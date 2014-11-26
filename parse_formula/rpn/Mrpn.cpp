/*
 * Mrpn.cpp
 *
 * YangZongze yangzongze@gmail.com
 */

#include "Mrpn.hpp"

void RPN::skipBlank() {
    while (index_ < originStr_.size() && 
            (originStr_[index_] == ' ' || originStr_[index_] == '\t' || originStr_[index_] == '\n')) {
        index_++;
    }
}

void RPN::getName(std::string & name) {
    skipBlank();
    if (index_ >= originStr_.size()) {
        name = END_NAME;
        return ;
    }

    size_t i = index_;
    char c = originStr_[index_];
    if (c >= '0' && c <= '9') {
        while ( i < originStr_.size() && 
                ((originStr_[i]>= '0' && originStr_[i] <= '9') || originStr_[i] == '.')) {
            i++;
        }
        name = originStr_.substr(index_, i - index_);
        index_ = i;
    } else if (isSimpleOP(c)) {
        name = c;
        index_++;
    } else {
        while ( i < originStr_.size() && 
                ((originStr_[i]>= 'a' && originStr_[i] <= 'z') || 
                 (originStr_[i]>= '0' && originStr_[i] <= '9') ||
                 (originStr_[i]>= 'A' && originStr_[i] <= 'Z') || originStr_[i] == '_')) {
            i++;
        }
        if (i == index_) {
            name = originStr_.substr(index_, 1); // error
        } else {
            name = originStr_.substr(index_, i - index_);
        }
        index_ = i;
    }
}
bool RPN::getNextElement(Element & ele) {
    std::string name; 
    getName(name);
    if (name == END_NAME) {
        return false;
    }
    if (isSysKey(name)) {
        ele = systemKeyEleMap.find(name)->second;
        return true;
    }
    if (isUserVar(name)) {
        ele = userKeyEleMap_.find(name)->second;
        return true;
    }
    if (isNumber(name)) {
        ele = Element(name, ET_CONSTNUM, -1);
        return true;
    }

    std::cout << " Error: Unkonw " << name << std::endl;
    return false;
}

void RPN::change()
{
    Element ele;
    while (getNextElement(ele)) {
        if (ele.isOp()) {
            while ((!opStack_.empty()) && ele <= opStack_.back()) {
                rpn_.push_back(opStack_.back());
                opStack_.pop_back();
            }
            if (ele == Left_B)
            {
                opStack_.push_back(Left_B_I);
            }else if(ele == Right_B) {
                opStack_.pop_back();
            }else if (ele == Seprate) {
                // do nothing
            }else {
                opStack_.push_back(ele);
            }
        } else {
            rpn_.push_back(ele);
        }
        // print();
    }

    while (!opStack_.empty()) {
        rpn_.push_back(opStack_.back());
        opStack_.pop_back();
    }
    std::cout << "OriginStr: " << originStr_ << std::endl;
    print();
}

void RPN::print()
{
    std::cout << "OpStack:   ";
    for (int i = 0; i < opStack_.size(); ++i) {
        std::cout << opStack_[i].str_ << " " ;
    }
    std::cout << std::endl;
    std::cout << "---RPN:    ";
    for (int i = 0; i < rpn_.size(); ++i) {
        std::cout << rpn_[i].str_ << " ";
    }
    std::cout << std::endl;
}

