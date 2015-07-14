/*
 * Mrpn.cpp
 *
 * YangZongze yangzongze@gmail.com
 */

#include "Mtoken.hpp"
#include "Mfunction.hpp"

FunctionBase::FunctionBase()
{}

FunctionBase::FunctionBase(std::string &var, std::string &expression)
        :variable_(var), expression_(expression) 
{}

FunctionBase::FunctionBase(char *var, char *expression)
        :variable_(var), expression_(expression) 
{}
FunctionBase::~FunctionBase() 
{}

void FunctionBase::init()
{
    rpnE_.setVar(variable_);
    rpnE_.transform(expression_);
    rpnE_.print();
}
double FunctionBase::compute(std::vector<double> v)
{
    return rpnE_.compute(v);
}

