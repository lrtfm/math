/*
 * Mrpn.hpp
 *
 * 2014-12-10  0:58:06
 *
 * YangZongze yangzongze@gmail.com
 */

#ifndef MRPN_HPP__
#define MRPN_HPP__

#include "Melement.hpp"
#include "Mtoken.hpp"
#include <map>
#include <stack>
#include <string>
#include <vector>

typedef std::map<std::string, Element> ElementMap;

class RPNexpression {
public:
    RPNexpression(){
        if (initFlag_ == false) {
            initStaticMembers();
            initFlag_ == true;
        }
    }
    void setVar(std::string & var);

    void transform(std::string & expression);
    double compute(std::vector<double> v);

    void print();
private:
    void initStaticMembers();
    Element getElementByName(std::string & name);
    void elementCompute(Element & ele, std::stack<double> & mem);

private:
    std::vector<std::string> var_;
    std::vector<Element> rpn_;

    static bool initFlag_;
    static Element Add;
    static Element Sub;
    static Element Mul;
    static Element Div;
    static Element Pow;
    static Element Lba;
    static Element Rba;
    static Element Com;
    static Element Lba_i;

    static Element Exp;
    static Element Sin;
    static Element Cos;

    static TokenRule numberRule_;
    static TokenProcess varProcess_;
    static TokenProcess rpnTokenProcess_;
    static ElementMap systemElementMap_;
};


#endif
