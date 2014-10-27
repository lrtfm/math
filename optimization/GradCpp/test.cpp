#include "GradientDescent.hpp"


class MyFun : public FunctionObject
{
public:
    virtual double function(const Mvector &x)
    {
        return x[0] * x[0] + x[1] * x[1] + x[0];
        // return 2*x[0] * x[0] + x[1] * x[1] + x[0];
    }
    virtual int getDimension() {
        return 2;
    }
};


int main(int argc, char **argv)
{
    MyFun myfun;
    GradientDescent gradDescent(myfun);

    Mvector ret(2);
    Mvector x0(2);
    x0[0] = 2;
    x0[1] = 3;
   
    x0.print("The initial x0");
    ret = gradDescent.solver(x0, 0.000001);
    ret.print("The return value");

    return 0;
}


