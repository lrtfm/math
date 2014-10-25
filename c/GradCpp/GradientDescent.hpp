#ifndef __GRADIENTDESCENT_HPP__
#define __GRADIENTDESCENT_HPP__
#include "Mvector.hpp"

class FunctionObject
{
public:
    double operator()(const Mvector &x) {
        return function(x);
    }

    virtual int getDimension() = 0;
    virtual double function(const Mvector &x) {
        return 0;
    }

    virtual ~FunctionObject(){}
};

class GradientDescent 
{
public:
    //GradientDescent()
    //{}

    GradientDescent(FunctionObject &fun) : fun_(fun)
    {}

    Mvector solver(const Mvector &x, double epsilon)
    {
        currX_ = x;
        currD_ = -1 * getGrad(currX_, epsilon);
        double alpha;
        double minAlpha, maxAlpha;

        while (currD_.getNorm() > epsilon) {
            advanceAndRetreat(10, &minAlpha, &maxAlpha);
            alpha = goldSection(minAlpha, maxAlpha, epsilon);
            currX_.print("X");
            currD_.print("D");
            std::cout << "alpha" << ":" << alpha << std::endl;
            currX_ = currX_ + alpha * currD_;
            currD_ = -1 * getGrad(currX_, epsilon);
        }

        return currX_;
    }

private:
    // 数值算法计算函数在某点处的梯度
    // { 8 * [f(x+h)-f(x-h)] - f(x+2h) + f(x-2h) } / 12h
    Mvector getGrad(const Mvector &x, double epsilon)
    {
        // std::cout << "Begin " << std::endl;
        double u1;
        double u2;
        double l;
        int d = fun_.getDimension();
        Mvector oGrad(d);
        Mvector nGrad(d);
        Mvector e;
        double h = 0.01;
        for (int i = 0; i < d; i++) {
            nGrad[i] = (fun_(x.delta(i, h)) - fun_(x.delta(i, -h)))/(2.0*h);
        }

        do {
            h = h/2.0;
            oGrad = nGrad;
            for (int i = 0; i < d; i++) {
                u1 = 8 * (fun_(x.delta(i, h)) - fun_(x.delta(i, -h)));
                u2 = fun_(x.delta(i, -2.0*h)) - fun_(x.delta(i, -2.0*h));
                l = 12.0*h;
                nGrad[i] = (u1 + u2) / l;
            }

            e = nGrad - oGrad;
        } while (e.getNorm() > epsilon);
        // std::cout << "End " << std::endl;
        
        return nGrad;
    }

    double funOfAlpha(double alpha)
    {
        Mvector x = currX_ + alpha * currD_;
        return fun_(x);
    }
        
    void advanceAndRetreat(double x, double *a, double *b)
    {
        double t = 2;
        double h = 0.1;
        if (funOfAlpha(x + h) > funOfAlpha(x)) {
            h = -h;
        }

        while (funOfAlpha(x + h) < funOfAlpha(x)) {
            x = x + h;
        }

        if (h > 0) {
            *a = x - h/2;
            *b = x + h;
        } else {
            *a = x + h;
            *b = x - h/2;
        }
    }
#define G 0.618
    double goldSection(double a, double b, double e)
    {
        double lambda = a + (1 - G)*(b - a);
        double mu = a + G * (b - a);

        while (a - b > e || b - a > e) {
            if (funOfAlpha(lambda) > funOfAlpha(mu)) {
                a = lambda;
                lambda = mu;
                // b do not change.
                mu = a + G * (b - a);
            }
            else {
                // a do not change.
                b = mu;
                mu = lambda;
                lambda = a + (1 - G) * (b - a);
            }
        }

        return lambda;
    }

private:
    Mvector currX_;
    Mvector currD_;
    FunctionObject &fun_;
};


#endif
