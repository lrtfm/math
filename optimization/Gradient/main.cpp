#include "GradientDescent.hpp"

double function(const Mvector &x)
{
    return x[0] * x[0] + x[1] * x[1] + x[0];
    // return 2*x[0] * x[0] + x[1] * x[1] + x[0];
}

double fun2(const Mvector &x)
{
    double a = x[0];
    double b = x[1];
    return 8 *a*a + b*b + 5*b + 30;
}

int main(int argc, char **argv)
{
    //FunctionObject myfun(function, 2);
    //GradientDescent gradDescent(myfun);
    GradientDescent gradDescent(FunctionObject(fun2, 2, "f = 8x^2 + y^2 + 5y + 30"));

    Mvector ret(2);
    Mvector x0(2);
    x0[0] = 20;
    x0[1] = 30;

    ret = gradDescent.gd_solver(x0, 0.000001);
    ret = gradDescent.cg_solver(x0, 0.000001);
    ret = gradDescent.dfp_solver(x0, 0.000001);

    //std::cout << "8x^2 + y^2 + 5y + 30" << std::endl;
    return 0;
}

