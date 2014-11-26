/*
 * Mrpn.hpp
 *
 * YangZongze yangzongze@gmail.com
 */

#ifndef MRPN_HPP__
#define MRPN_HPP__
#include "Melement.hpp"

class RPN {
public:
    RPN(char *str) : originStr_(str), index_(0)
    {}
    RPN(const std::string & str) : originStr_(str), index_(0)
    {}
    bool getNextElement(Element & ele);
    void change();
    void print();
private:
    void skipBlank();
    void getName(std::string & name);
    bool isSysKey(std::string & name) {
        return systemKeyEleMap.find(name) != systemKeyEleMap.end();
    }
    bool isUserVar(std::string &name) {
        return userKeyEleMap_.find(name) != userKeyEleMap_.end();
    }
    bool isNumber(std::string &name) {
        return (name[0] >= '0' && name [0] <= '9');
    }

    bool isSimpleOP(char c) {
        return (c == '+' || c == '-' || c == '*' || 
                c == '/' || c == '^' || c == '(' || 
                c == ',' || c == ')');
    }

private:
    size_t index_;
    std::string originStr_;
    std::vector<Element> opStack_;
    std::vector<Element> rpn_;
    KeyElementMap userKeyEleMap_;
};

#endif 
