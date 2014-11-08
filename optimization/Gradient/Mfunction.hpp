#ifndef __MFUNCTION_HPP__
#define __MFUNCTION_HPP__
#include "Mvector.hpp"

typedef double (*MutilFun)(const Mvector &x);

class FunctionObject{
public:
    FunctionObject(MutilFun fun, int n) : dim_(n), mfun_(fun)
    {
        x_.setDim(n);
        grad_.setDim(n);
        if (n == 1) {
            x_[0] = 1.0;
            grad_[0] = 0.0;
        }
    }

    void setToOneD(const Mvector &x, const Mvector &grad)
    {
        x_ = x;
        grad_ = grad;
    }

    int getDimension() {
        return dim_;
    }

    double operator()(const Mvector &x) {
        return mfun_(x);
    }

    double operator()(double alpha) {
        Mvector x = x_ + alpha * grad_;
        return mfun_(x);
    }

private:
    int dim_;
    MutilFun mfun_;
    Mvector x_;
    Mvector grad_;
};
#endif
