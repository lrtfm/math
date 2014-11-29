/*
 * Mrpn.cpp
 *
 * YangZongze yangzongze@gmail.com
 */

#include "Mtoken.hpp"
#include "Msys.hpp"
#include "Mrpn.hpp"

FunctionBase::FunctionBase() : needInit_(true)
{}

FunctionBase::FunctionBase(std::string &var, std::string &expression)
        : needInit_(true), variable_(var), expression_(expression) 
{}

FunctionBase::FunctionBase(char *var, char *expression)
        : needInit_(true), variable_(var), expression_(expression) 
{}
FunctionBase::~FunctionBase() 
{}

void FunctionBase::setVar(std::string &var) 
{
    variable_ = var;
    needInit_ = true;
}

void FunctionBase::setExpression(std::string &expression)
{
    expression_ = expression;
    needInit_ = true;
}

void FunctionBase::init() 
{
    if (needInit_) {
        initElementManger();
        rpnTranform();
        needInit_ = false;
    }
}

void FunctionBase::initElementManger()
{
    try {
        eleManager_.init(variable_);
    }
    catch (UnknowToken & e) {
        std::cout << std::endl << e.info() << std::endl;
    }
}

bool FunctionBase::getNextElement(size_t & index, Element & ele) {
    std::string name;
    if (!MC::tokenProcess.getToken(expression_, index, name)) {
        return false;
    }
    ele = eleManager_.getElementByName(name);
    return true;
}

void FunctionBase::rpnTranform()
{
    Element ele;
    size_t index = 0;
    std::vector<Element> opStack_;
    try {
        while (getNextElement(index, ele)) {
            if (ele.isOp()) {
                while ((!opStack_.empty()) && ele <= opStack_.back()) {
                    rpn_.push_back(opStack_.back());
                    opStack_.pop_back();
                }
                if (ele == MC::Lba)
                {
                    opStack_.push_back(MC::Lba_i);
                }else if(ele == MC::Rba) {
                    opStack_.pop_back();
                }else if (ele == MC::Com) {
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

void FunctionBase::print()
{
    init();
    std::cout << std::endl;
    std::cout << "---RPN:    ";
    for (int i = 0; i < rpn_.size(); ++i) {
        std::cout << rpn_[i].str_ << " ";
    }
    std::cout << std::endl;
}

