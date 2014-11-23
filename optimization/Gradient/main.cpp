#include "GradientDescent.hpp"
#include <cmath>

double fun1(const Mvector &x) {
    double a = x[0];
    double b = x[1];
    return 8 *a*a + b*b + 5*b + 30;
}

double fun2(const Mvector &x) {
    double a = x[0];
    double b = x[1];
    return exp(a*a + b*b + 2*b + 1);// + exp(-a*a - b*b - 2*b - 1);
}
double d1fun2(const Mvector &x) {
    double a = x[0];
    double b = x[1];
    return 2*a*exp(a*a + b*b + 2*b + 1);// + exp(-a*a - b*b - 2*b - 1);
}

double d2fun2(const Mvector &x) {
    double a = x[0];
    double b = x[1];
    return (2*b + 2)*exp(a*a + b*b + 2*b + 1);// + exp(-a*a - b*b - 2*b - 1);
}

int main(int argc, char **argv) {
    GradientDescent gradDescent(FunctionObject(fun1, 2, "f = 8x^2 + y^2 + 5y + 30"));

    Mvector ret(2);
    Mvector x0(2);
    x0[0] = 20;
    x0[1] = 30;

    ret = gradDescent.gd_solver(x0, 0.000001);
    ret = gradDescent.cg_solver(x0, 0.000001);
    ret = gradDescent.dfp_solver(x0, 0.000001);
    ret = gradDescent.pattern_solver(x0, 0.000001);

    x0[0] = 1;
    x0[1] = 0;
    GradientDescent gd(FunctionObject(fun2, 2, "f = exp(x^2 + y^2 + 2y + 1)"));
    ret = gd.gd_solver(x0, 0.000001);
    ret = gd.cg_solver(x0, 0.000001);
    ret = gd.dfp_solver(x0, 0.000001);
    ret = gd.pattern_solver(x0, 0.000001);

    x0[0] = 10;
    x0[1] = 5;
    ret = gd.gd_solver(x0, 0.00001);
    ret = gd.cg_solver(x0, 0.00001);
    ret = gd.dfp_solver(x0, 0.00001);
    ret = gd.pattern_solver(x0, 0.000001);

    FunctionObject fund(fun2, 2, "f = exp(x^2 + y^2 + 2y + 1) whit solution d");
    std::vector<MutilFun> df;
    df.push_back(d1fun2);
    df.push_back(d2fun2);
    fund.setDerivative(df);
    GradientDescent gd2(fund);
    x0[0] = 10;
    x0[1] = 5;
    ret = gd2.gd_solver(x0, 0.000001);
    ret = gd2.cg_solver(x0, 0.000001);
    ret = gd2.dfp_solver(x0, 0.000001);
    ret = gd2.pattern_solver(x0, 0.000001);

    return 0;
}

