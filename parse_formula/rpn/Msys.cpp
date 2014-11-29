/*
 * Msys.cpp
 *
 * YangZongze yangzongze@gmail.com
 */

#include "Msys.hpp"
#include <cmath>
#include <stack>

namespace MC {

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

TokenProcess tokenProcess(blankRule, ruleVect);
TokenProcess varProcess(sepVarRule, varRuleVect);
TokenProcess numProcess(sepVarRule, numRuleVect);

const char *ADD = "+";
const char *SUB = "-";
const char *MUL = "*";
const char *DIV = "/";
const char *POW = "^";
const char *LBA = "(";
const char *COM = ",";
const char *RBA = ")";
Element Add(ADD, ET_OPERATOR, 3);
Element Sub(SUB, ET_OPERATOR, 3);
Element Mul(MUL, ET_OPERATOR, 4);
Element Div(DIV, ET_OPERATOR, 4);
Element Pow(POW, ET_OPERATOR, 6);
Element Lba(LBA, ET_OPERATOR, 7);
Element Com(COM, ET_OPERATOR, 2);
Element Rba(RBA, ET_OPERATOR, 2);
Element Lba_i(LBA, ET_OPERATOR, 1);

// inner function
const char *EXP = "exp";
const char *SIN = "sin";
const char *COS = "cos";
Element Exp(EXP, ET_OPERATOR, 5);
Element Sin(SIN, ET_OPERATOR, 5);
Element Cos(COS, ET_OPERATOR, 5);

const KeyElementMap::value_type  systemKeyPair[] =
{
    KeyElementMap::value_type(ADD, Add),
    KeyElementMap::value_type(SUB, Sub),
    KeyElementMap::value_type(MUL, Mul),
    KeyElementMap::value_type(DIV, Div),
    KeyElementMap::value_type(POW, Pow),
    KeyElementMap::value_type(LBA, Lba),
    KeyElementMap::value_type(COM, Com),
    KeyElementMap::value_type(RBA, Rba),
    KeyElementMap::value_type(EXP, Exp),
    KeyElementMap::value_type(SIN, Sin),
    KeyElementMap::value_type(COS, Cos),
};
KeyElementMap systemKeyMap(systemKeyPair, systemKeyPair + 11); 
ElementClass systemElementClass(&systemKeyMap);
NumberElementClass numberElementClass;

void compute(Element & ele, std::stack<double> & mem)
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

}
