/*
 * Mfunction.hpp
 *
 * 2014-12-11  1:30:09
 *
 * YangZongze yangzongze@gmail.com
 */


#ifndef MFUNCTION_HPP__
#define MFUNCTION_HPP__

#include "Mrpn.hpp"
#include <vector>
#include <string>

class FunctionBase {
public:
    FunctionBase();

    FunctionBase(std::string &var, std::string &expression);
    FunctionBase(char *var, char *expression);

    virtual ~FunctionBase();

    void init();
    double compute(std::vector<double> v);

private:
    std::string variable_;
    std::string expression_;

    RPNexpression rpnE_;
};

#endif 
