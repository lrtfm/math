/*
 * Mrpn.hpp
 *
 * YangZongze yangzongze@gmail.com
 */

#ifndef MRPN_HPP__
#define MRPN_HPP__
#include "Mtoken.hpp"
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
    bool isSysKey(std::string & name) {
        return systemKeyEleMap_.find(name) != systemKeyEleMap_.end();
    }
    bool isUserVar(std::string &name) {
        return userKeyEleMap_.find(name) != userKeyEleMap_.end();
    }
    bool isNumber(std::string &name) {
        return (name[0] >= '0' && name [0] <= '9');
    }

private:
    size_t index_;
    std::string originStr_;
    std::vector<Element> opStack_;
    std::vector<Element> rpn_;
    KeyElementMap userKeyEleMap_;
    static KeyElementMap systemKeyEleMap_;
    static TokenProcess tokenProcess_;
};

#endif 
