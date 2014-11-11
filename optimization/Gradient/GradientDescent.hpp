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

    Mvector gd_solver(const Mvector &x, double epsilon)
    {
        Mvector cx = x;
        Mvector grad = getGrad(cx, epsilon);
        Mvector d = -1 * grad;
        double alpha;
        double minAlpha, maxAlpha;
        int i = 0;

        while (grad.getNorm() > epsilon) {
            i++;
            alpha = oneDimSearch(cx, d, epsilon);
            cx = cx + alpha * d;
            grad = getGrad(cx, epsilon);
            d = -1 * grad;
        }
        output("Gradient descent method", x, cx, i); 
        return cx;
    }

    // 共轭梯度方法
    Mvector cg_solver(const Mvector &x, double epsilon)
    {
        Mvector cx = x;
        Mvector ograd = getGrad(cx, epsilon);
        Mvector grad;
        Mvector d = -1 * ograd;
        double alpha;
        double beta;
        int i = 0;

        while (ograd.getNorm() > epsilon) {
            i++;
            alpha = oneDimSearch(cx, d, epsilon);
            cx = cx + alpha * d;
            grad = getGrad(cx, epsilon);
            beta = ((transform(grad) * grad ) / (transform(ograd) * ograd))(0,0);
            d = -1 * grad + beta * d;
            ograd = grad;
        }

        output("Conjugate gradient method", x, cx, i);
        return cx;
    }

    Mvector dfp_solver(const Mvector &x, double epsilon)
    {
        Mvector ox = x;
        Mvector cx;
        Mmatrix H = Mmatrix::E(fun_.getDimension());
        Mvector ograd = getGrad(ox, epsilon);
        Mvector grad;
        Mvector d;
        Mvector s;
        Mvector y;
        double alpha;
        int i = 0;

        while (ograd.getNorm() > epsilon) {
            i++;
            d = -1 * H * ograd;
            alpha = oneDimSearch(ox, d, epsilon);
            cx = ox + alpha * d;
            grad = getGrad(cx, epsilon);
            s = cx - ox;
            y = grad - ograd;
            H = H + (s * transform(s)) / (transform(s) * y) 
                - (H * y * transform(y) * H) / (transform(y) * H * y);
            ograd = grad;
            ox = cx;
        }

        output("DFP method result for ", x, cx, i);
        return cx;
    }

private:

    double oneDimSearch(const Mvector & x, const Mvector & d, double epsilon)
    {
        double alpha;
        double minAlpha, maxAlpha;
        fun_.setToOneD(x, d);
        MSP::advanceAndRetreat(fun_, 10, &minAlpha, &maxAlpha);
        alpha = MSP::goldSection(fun_, minAlpha, maxAlpha, epsilon);
        return alpha;
    }

    void output(const std::string & s,const Mvector & x, const Mvector &cx, int i) {
        std::cout << s << " for function " << fun_.info() << ":" << std::endl
                  << "\tThe begin point: " << transform(x) << "'" << std::endl
                  << "\tThe result point: " << transform(cx) << "'" << std::endl
                  << "\tIterator times: " << i << std::endl << std::endl;
    }

    // 数值算法计算函数在某点处的梯度
    // { 8 * [f(x+h)-f(x-h)] - f(x+2h) + f(x-2h) } / 12h
    Mvector getGrad(const Mvector &x, double epsilon)
    {
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

#endif

