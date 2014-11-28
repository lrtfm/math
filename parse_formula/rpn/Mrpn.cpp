/*
 * Mrpn.cpp
 *
 * YangZongze yangzongze@gmail.com
 */

#include "Mtoken.hpp"
#include "Msys.hpp"
#include "Mrpn.hpp"

TokenProcess RPN::tokenProcess_(MC::blankRule, MC::ruleVect);
KeyElementMap RPN::systemKeyEleMap_(
        MC::systemKeyMap.begin(), MC::systemKeyMap.end()); 

bool RPN::getNextElement(Element & ele) {
    std::string name;
    if (tokenProcess_.getToken(originStr_, index_, name)) {
        if (isSysKey(name)) {
            ele = systemKeyEleMap_.find(name)->second;
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
        throw UnknowToken(" in RPN::getNextElement " + name);
    }
    return false;
}

void RPN::change()
{
    Element ele;
    try {
        while (getNextElement(ele)) {
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

