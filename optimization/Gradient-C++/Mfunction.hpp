/*
 * Mfunction.hpp
 *
 * 2014-12-23  1:02:10
 *
 * YangZongze yangzongze@gmail.com
 */

#ifndef MFUNCTION_HPP__
#define MFUNCTION_HPP__
#include "Mcommon.hpp"
#include "Mvector.hpp"

typedef double (*MutilFun)(const Mvector &x);

class FunctionObject {
public:
    FunctionObject(MutilFun fun, int n) : dim_(n), mfun_(fun), isSetD_(false) { init(n);}

    FunctionObject(MutilFun fun, int n, const std::string & s) 
        : dim_(n), mfun_(fun), str_(s), isSetD_(false) {
        init(n);
    }

    void setToOneD(const Mvector &x, const Mvector &grad) {
        x_ = x;
        grad_ = grad;
    }

    void setDerivative(const std::vector<MutilFun> & df) {
    	isSetD_ = true;
    	derivative_ = df;
    }

    int getDimension() { return dim_; }

    double operator()(const Mvector &x) { return mfun_(x); }

    double operator()(double alpha) {
        Mvector x = x_ + alpha * grad_;
        return mfun_(x);
    }

    const std::string & info() const {
        return str_;
    }

    Mvector getGrad(const Mvector &x, double epsilon) {
        Mvector ret(dim_);
        if (isSetD_) {
            for (int i = 0; i < dim_; ++i) {
                ret[i] = derivative_[i](x);
            }

        } else {
            ret = getGrad_inner(x, epsilon);
        }

        // ret.normalize();
        return ret;
    }

private:
    void init(int n) {
        x_.setDim(n);
        grad_.setDim(n);
        if (n == 1) {
            x_[0] = 1.0;
            grad_[0] = 0.0;
        }
    }

    // 数值算法计算函数在某点处的梯度
    // { 8 * [f(x+h)-f(x-h)] - f(x+2h) + f(x-2h) } / 12h
    Mvector getGrad_inner(const Mvector &x, double epsilon) {
        double u1, u2, l;
        Mvector oGrad(dim_);
        Mvector nGrad(dim_);
        Mvector e;
        double h = 0.01;
        for (int i = 0; i < dim_; i++) {
            nGrad[i] = (mfun_(x.delta(i, h)) - mfun_(x.delta(i, -h)))/(2.0*h);
        }

        do {
            h = h/2.0;
            oGrad = nGrad;
            for (int i = 0; i < dim_; i++) {
                u1 = 8 * (mfun_(x.delta(i, h)) - mfun_(x.delta(i, -h)));
                u2 = mfun_(x.delta(i, -2.0*h)) - mfun_(x.delta(i, -2.0*h));
                l = 12.0*h;
                nGrad[i] = (u1 + u2) / l;
            }
            e = nGrad - oGrad;
        } while (h > MC::epsilon && e.getNorm() > epsilon);

        return nGrad;
    }

    int dim_;
    std::string str_;
    MutilFun mfun_;
    Mvector x_;
    Mvector grad_;
    bool isSetD_;
    std::vector<MutilFun> derivative_;
};

#endif
