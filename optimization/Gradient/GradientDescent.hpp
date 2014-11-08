#ifndef __GRADIENTDESCENT_HPP__
#define __GRADIENTDESCENT_HPP__
#include "Mvector.hpp"
#include "Mmatrix.hpp"
#include "Mfunction.hpp"
#include "OneDimSearch.hpp"

class GradientDescent 
{
public:
    GradientDescent(FunctionObject fun) : fun_(fun)
    {
        inner_epsilon_ = 0.000001;
    }


    Mvector solver(const Mvector &x, double epsilon)
    {
        Mvector cx = x;
        Mvector grad = -1 * getGrad(cx, epsilon);
        double alpha;
        double minAlpha, maxAlpha;
        int i = 0;

        while (grad.getNorm() > epsilon) {
            i++;
        x.print("DEBUG1");
            fun_.setToOneD(cx, grad);
        x.print("DEBUG2");
            MSP::advanceAndRetreat(fun_, 10, &minAlpha, &maxAlpha);
            alpha = MSP::goldSection(fun_, minAlpha, maxAlpha, epsilon);
            // std::cout << "alpha" << ":" << alpha << std::endl;
            cx = cx + alpha * grad;
            grad = -1 * getGrad(cx, epsilon);
        }
        std::cout << "G Result Info:" << std::endl;
        x.print("\tThe begin point");
        cx.print("\tThe result point");
        std::cout << "\tIterator times: " << i << std::endl;

        return cx;
    }

    // 共轭梯度方法
    Mvector solver2(const Mvector &x, double epsilon)
    {
        Mvector cx = x;
        // Mmatrix hessian = getHessian(cx, epsilon);
        Mvector ograd = getGrad(cx, epsilon);
        Mvector grad;
        Mvector od = -1 * ograd;
        Mvector d;
        double alpha;
        double beta;
        double minAlpha, maxAlpha;
        int i = 0;

        while (ograd.getNorm() > epsilon) {
            i++;
            fun_.setToOneD(cx, od);
            MSP::advanceAndRetreat(fun_, 10, &minAlpha, &maxAlpha);
            alpha = MSP::goldSection(fun_, minAlpha, maxAlpha, epsilon);
            //std::cout << "alpha" << ":" << alpha << std::endl;
            cx = cx + alpha * od;
            grad = getGrad(cx, epsilon);
            beta = grad * grad / (ograd * ograd);
            d = -1 * grad + beta * od;
            od = d;
            ograd = grad;
        }

        std::cout << "CG Result Info:" << std::endl;
        x.print("\tThe begin point");
        cx.print("\tThe result point");
        std::cout << "\tIterator times: " << i << std::endl;

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
        } while (h > inner_epsilon_ && e.getNorm() > epsilon);
        // std::cout << "End " << std::endl;
        
        return nGrad;
    }

    /*
    Mmatrix getHessian(const Mvector &x, double epsilon)
    {
        // std::cout << "Begin " << std::endl;
        double n = 0.0;
        double o = 0.0;
        double h = 0.0;
        int d = fun_.getDimension();
        Mmatrix hessian(d);
        for (int i = 0; i < d; ++i) {
            for (int j = i; i < d; ++j) {
                h = 0.01;
                // 重复代码 TODO
                n = fun_(x.delta(i, h, j, h)) - fun_(x.delta(i, -h, j, h)) 
                   - fun_(x.delta(i, h, j, -h)) + fun_(x.delta(i, -h, j, -h));
                n = n / (4 * h * h);

                do {
                    h = h / 2;
                    o = n;
                    n = fun_(x.delta(i, h, j, h)) - fun_(x.delta(i, -h, j, h)) 
                       - fun_(x.delta(i, h, j, -h)) + fun_(x.delta(i, -h, j, -h));
                    n = n / (4 * h * h);
                } while (h > inner_epsilon_ && (n - o > epsilon || n - o < -epsilon))

                hessian(i, j) = n;
                hessian(j, i) = n;
            }
        }

        return hessian;
    }
    */


private:
    FunctionObject fun_;
    double inner_epsilon_;
};

// static double GradientDescent::inner_epsilon_ = 0.00001;

#endif
