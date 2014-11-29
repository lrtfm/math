/*
 * Mrpn.hpp
 *
 * YangZongze yangzongze@gmail.com
 */

#ifndef MRPN_HPP__
#define MRPN_HPP__
#include "Mtoken.hpp"
#include "Melement.hpp"

class FunctionBase {
public:
    FunctionBase();

    FunctionBase(std::string &var, std::string &expression);
    FunctionBase(char *var, char *expression);

    virtual ~FunctionBase();

    void setVar(std::string & var);
    void setExpression(std::string & expression);

    void print();

private:

    void init(); 
    void initElementManger();

    // for RPN tranform
    void rpnTranform();
    bool getNextElement(size_t & index, Element & ele);

private:
    bool needInit_;
    std::string variable_;
    std::string expression_;

    ElementManager eleManager_;

    std::vector<Element> rpn_;
};

#endif 
