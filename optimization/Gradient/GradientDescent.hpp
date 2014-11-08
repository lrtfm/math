#ifndef __GRADIENTDESCENT_HPP__
#define __GRADIENTDESCENT_HPP__
#include "Mvector.hpp"
#include "Mfunction.hpp"
#include "OneDimSearch.hpp"

class GradientDescent 
{
public:
    GradientDescent(FunctionObject fun) : fun_(fun)
    {}

    Mvector solver(const Mvector &x, double epsilon)
    {
        Mvector cx = x;
        Mvector grad = -1 * getGrad(cx, epsilon);
        double alpha;
        double minAlpha, maxAlpha;

        while (grad.getNorm() > epsilon) {
            fun_.setToOneD(cx, grad);
            MSP::advanceAndRetreat(fun_, 10, &minAlpha, &maxAlpha);
            alpha = MSP::goldSection(fun_, minAlpha, maxAlpha, epsilon);
            std::cout << "alpha" << ":" << alpha << std::endl;
            cx = cx + alpha * grad;
            grad = -1 * getGrad(cx, epsilon);
        }

        return cx;
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

private:
    FunctionObject &fun_;
};

#endif
