/*
 * Mrpn.cpp
 *
 * 2014-12-10 23:21:33
 *
 * YangZongze yangzongze@gmail.com
 */

#include "Mrpn.hpp"
#include <cmath>
#include <algorithm>

bool RPNexpression::initFlag_ = false;
Element RPNexpression::Add;
Element RPNexpression::Sub;
Element RPNexpression::Mul;
Element RPNexpression::Div;
Element RPNexpression::Pow;
Element RPNexpression::Lba;
Element RPNexpression::Rba;
Element RPNexpression::Com;
Element RPNexpression::Lba_i;
Element RPNexpression::Exp;
Element RPNexpression::Sin;
Element RPNexpression::Cos;
TokenRule  RPNexpression::numberRule_;
TokenProcess RPNexpression::varProcess_;
TokenProcess RPNexpression::rpnTokenProcess_;
ElementMap RPNexpression::systemElementMap_;

void RPNexpression::initStaticMembers()
{
    char dot = '.';
    char underLine = '_';
    std::string blank(" \n\t");
    std::string num("0123456789");
    std::string simpOp("+-*/^(,)");
    std::string alphabet("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

    TokenRule blankRule(blank);
    TokenRule numRule(num + dot, num, num);
    TokenRule keyRule(alphabet + num + underLine, alphabet + underLine);
    TokenRule sopRule(simpOp);
    TokenRule sepVarRule(blank + simpOp);

    TokenRule rules[] = { numRule, keyRule, sopRule};
    std::vector<TokenRule> ruleVect(rules, rules + 3);
    std::vector<TokenRule> varRuleVect(rules + 1, rules + 2);
    std::vector<TokenRule> numRuleVect(rules, rules + 1);

    numberRule_ = numRule;
    varProcess_ = TokenProcess(sepVarRule, varRuleVect);
    rpnTokenProcess_ = TokenProcess(blankRule, ruleVect);

    const char *ADD = "+";
    const char *SUB = "-";
    const char *MUL = "*";
    const char *DIV = "/";
    const char *POW = "^";
    const char *LBA = "(";
    const char *COM = ",";
    const char *RBA = ")";
    Add = Element(ADD, ET_OPERATOR, 3);
    Sub = Element(SUB, ET_OPERATOR, 3);
    Mul = Element(MUL, ET_OPERATOR, 4);
    Div = Element(DIV, ET_OPERATOR, 4);
    Pow = Element(POW, ET_OPERATOR, 6);
    Lba = Element(LBA, ET_OPERATOR, 7);
    Com = Element(COM, ET_OPERATOR, 2);
    Rba = Element(RBA, ET_OPERATOR, 2);
    Lba_i = Element(LBA, ET_OPERATOR, 1);

    // inner function
    const char *EXP = "exp";
    const char *SIN = "sin";
    const char *COS = "cos";
    Exp = Element(EXP, ET_OPERATOR, 5);
    Sin = Element(SIN, ET_OPERATOR, 5);
    Cos = Element(COS, ET_OPERATOR, 5);

    systemElementMap_.insert(ElementMap::value_type(ADD, Add));
    systemElementMap_.insert(ElementMap::value_type(SUB, Sub));
    systemElementMap_.insert(ElementMap::value_type(MUL, Mul));
    systemElementMap_.insert(ElementMap::value_type(DIV, Div));
    systemElementMap_.insert(ElementMap::value_type(POW, Pow));
    systemElementMap_.insert(ElementMap::value_type(LBA, Lba));
    systemElementMap_.insert(ElementMap::value_type(COM, Com));
    systemElementMap_.insert(ElementMap::value_type(RBA, Rba));
    systemElementMap_.insert(ElementMap::value_type(EXP, Exp));
    systemElementMap_.insert(ElementMap::value_type(SIN, Sin));
    systemElementMap_.insert(ElementMap::value_type(COS, Cos));
}
void RPNexpression::setVar(std::string &var)
{
    std::string token;
    size_t index = 0;
    while (varProcess_.getToken(var, index, token)) {
        var_.push_back(token);
    }
}

void RPNexpression::transform(std::string & expression)
{
    Element ele;
    std::string name;
    size_t index = 0;
    std::vector<Element> opStack_;
    try {
        while (rpnTokenProcess_.getToken(expression, index, name)) {
            ele = getElementByName(name);
            if (!ele.isValid()) {
                // error todo
                throw UnknowToken();
             }
            if (ele.isOp()) {
                while ((!opStack_.empty()) && ele <= opStack_.back()) {
                    rpn_.push_back(opStack_.back());
                    opStack_.pop_back();
                }
                if (ele == Lba)
                {
                    opStack_.push_back(Lba_i);
                }else if(ele == Rba) {
                    opStack_.pop_back();
                }else if (ele == Com) {
                    // do nothing
                }else {
                    opStack_.push_back(ele);
                }
            } else {
                rpn_.push_back(ele);
            } 
        }
        while (!opStack_.empty()) {
            rpn_.push_back(opStack_.back());
            opStack_.pop_back();
        }
    }
    catch (UnknowToken & e) {
        std::cout << std::endl << e.info() << std::endl;
    }
}

Element RPNexpression::getElementByName(std::string &name) {
    Element ele;
    if (systemElementMap_.find(name) != systemElementMap_.end()) {
        ele = systemElementMap_[name];
    } else if (find(var_.begin(), var_.end(), name) != var_.end()) {
        ele = Element(name, ET_VARIATION, -1);
    } else if (numberRule_.isMatchRule(name)) {
        ele = Element(name, ET_CONSTNUM, -1);
    } else {
        // ele is invalid
    }
    return ele;
}
double RPNexpression::compute(std::vector<double> v)
{
    size_t n = v.size();
    double value;
    std::stack<double> memory;

    for (int i = 0; i < rpn_.size(); ++i) {
        switch (rpn_[i].getType()) {
            case ET_CONSTNUM: 
                memory.push(atof(rpn_[i].getName().c_str()));
                break;
            case ET_VARIATION:
                value = 0;
                // how to process error
                for (size_t j = 0; j < var_.size() && j < n; ++j) {
                    if (rpn_[i].getName() == var_[j]) {
                        value = v[j];
                        break;
                    }
                }
                memory.push(value);
                break;
            case ET_OPERATOR:
                elementCompute(rpn_[i], memory);
                break;
            default:
                // error
                break;
        }
    }

    if (memory.size() == 1) {
        return memory.top();
    } else {
        // error
        return 0;
    }
}

void RPNexpression::elementCompute(Element & ele, std::stack<double> & mem)
{
    double x, y, z, ret;
    if (ele == Add) {
            y = mem.top(); mem.pop();
            x = mem.top(); mem.pop();
            ret = x + y;
            mem.push(ret);
    } else if (ele == Sub) {
            y = mem.top(); mem.pop();
            x = mem.top(); mem.pop();
            ret = x - y;
            mem.push(ret);
    } else if (ele == Mul) {
            y = mem.top(); mem.pop();
            x = mem.top(); mem.pop();
            ret = x * y;
            mem.push(ret);
    } else if (ele == Div) {
            y = mem.top(); mem.pop();
            x = mem.top(); mem.pop();
            ret = x / y;
            mem.push(ret);
    } else if (ele == Pow) {
            y = mem.top(); mem.pop();
            x = mem.top(); mem.pop();
            ret = pow(x,y);
            mem.push(ret);
    } else if (ele == Exp) {
            x = mem.top(); mem.pop();
            ret = exp(x);
            mem.push(ret);
    } else if (ele == Sin) {
            x = mem.top(); mem.pop();
            ret = sin(x);
            mem.push(ret);
    } else if (ele == Cos) {
            x = mem.top(); mem.pop();
            ret = cos(x);
            mem.push(ret);
    } else {
            //error
    }
}
void RPNexpression::print()
{
    std::cout << std::endl;
    std::cout << "---RPN:    ";
    for (int i = 0; i < rpn_.size(); ++i) {
        std::cout << rpn_[i].str_ << " ";
    }
    std::cout << std::endl;
}
