/*
 * GradientDescent.hpp
 *
 * 2014-12-23  1:01:20
 *
 * YangZongze yangzongze@gmail.com
 */

#ifndef GRADIENTDESCENT_HPP__
#define GRADIENTDESCENT_HPP__
#include "Mvector.hpp"
#include "Mmatrix.hpp"
#include "Mfunction.hpp"
#include "OneDimSearch.hpp"

class GradientDescent {
public:
    GradientDescent(FunctionObject fun) : fun_(fun) { } 

    Mvector gd_solver(const Mvector &x, double epsilon) {
        Mvector cx = x;
        Mvector grad = fun_.getGrad(cx, epsilon);
        Mvector d = -1 * grad;
        double alpha;
        int i = 0;

        while (grad.getNorm() > epsilon) {
            i++;
            d.normalize(); // 防止d过大引起函数溢出
            alpha = oneDimSearch(cx, d, epsilon);
            cx = cx + alpha * d;
            grad = fun_.getGrad(cx, epsilon);
            d = -1 * grad;
            Debug("i=" << i << ", grad =" << grad << ", d = " << d 
                             << ", cx =" << transform(cx) << "'" << std::endl);
        }
        output("Gradient descent method", x, cx, i); 
        return cx;
    }

    // 共轭梯度方法
    Mvector cg_solver(const Mvector &x, double epsilon) {
        Mvector cx = x;
        Mvector grad, ograd = fun_.getGrad(cx, epsilon);
        Mvector d = -1 * ograd;
        d.normalize(); // 防止d过大引起函数溢出
        double alpha, beta;
        int i = 0;

        while (ograd.getNorm() > epsilon) {
            i++;
            alpha = oneDimSearch(cx, d, epsilon);
            cx = cx + alpha * d;
            grad = fun_.getGrad(cx, epsilon);
            beta = ((transform(grad) * grad )/(transform(ograd) * ograd))(0,0);
            d = -1 * grad + beta * d;
            ograd = grad;
            Debug("i=" << i << ", grad =" << grad << ", d = " << d 
                             << ", cx =" << transform(cx) << "'" << std::endl);
        }

        output("Conjugate gradient method", x, cx, i);
        return cx;
    }

    Mvector dfp_solver(const Mvector &x, double epsilon) {
        Mvector cx, ox = x;
        Mmatrix H = Mmatrix::E(fun_.getDimension());
        Mvector ograd = fun_.getGrad(ox, epsilon);
        ograd.normalize(); // 大梯度溢出
        Mvector grad, d, s, y;
        double alpha;
        int i = 0;

        while (ograd.getNorm() > epsilon) {
            i++;
            d = -1 * H * ograd;
            alpha = oneDimSearch(ox, d, epsilon);
            cx = ox + alpha * d;
            grad = fun_.getGrad(cx, epsilon);
            s = cx - ox;
            y = grad - ograd;
            H = H + (s * transform(s)) / (transform(s) * y) 
                - (H * y * transform(y) * H) / (transform(y) * H * y);
            ograd = grad;
            ox = cx;
        }

        output("DFP method result", x, cx, i);
        return cx;
    }

    Mvector pattern_solver(const Mvector &x, double epsilon) {
        int n = fun_.getDimension();
        Mvector ox, cx = x;
        Mvector d, y = cx;
        Mvector e(n);
        Mvector tmp;
        double delta = 2;
        double alpha, beta = 2; //beta importan!!!
        int k = 0;
        int flag = 0;

        while (delta > epsilon) {
            k++;
            for (int i = 0; i < n; ++ i) {
                if (fun_(y + delta*e.delta(i, 1)) < fun_(y)) {
                    y = y + delta*e.delta(i, 1);
                } else if (fun_(y - delta*e.delta(i, 1)) < fun_(y)) {
                    y = y - delta*e.delta(i, 1);
                }
            }

            Debug("k=" << k << ", delta =" << delta << ", alpha = " << alpha
                             << ", " << transform(y) << "'" << ", d = " << d << std::endl);
            if (fun_(y) < fun_(cx)) {
                ox = cx;
                cx = y;
                d = cx - ox;
                alpha = oneDimSearch(cx, d, epsilon);
                y = cx + alpha*d;
                tmp = y - cx;
                Debug("y = " << transform(y) << "'" << ", cx = " << cx << std::endl);
                // 当y cx很接近时我们也认为收敛到了极小值点
                if (tmp.getNorm() < epsilon) {
                    flag++;
                    if (flag > 10) {
                        break;
                    }
                }
            } else {
                flag = 0;
                delta = delta / beta;
                y = cx;
            }
        }
        output("Hooke-Jeeves method result", x, cx, k);
        return cx;
    }

private:
    double oneDimSearch(const Mvector & x, const Mvector & d, double epsilon) {
        double alpha, minAlpha, maxAlpha;
        fun_.setToOneD(x, d);
        MSP::advanceAndRetreat(fun_, 1, &minAlpha, &maxAlpha);
        alpha = MSP::goldSection(fun_, minAlpha, maxAlpha, epsilon);
        return alpha;
    }

    void output(const std::string & s,const Mvector & x, const Mvector &cx, int i) {
        std::cout << s << " for function " << fun_.info() << ":" << std::endl
                  << "\tThe begin point: " << transform(x) << "'" << std::endl
                  << "\tThe result point: " << transform(cx) << "'" << std::endl
                  << "\tIterator times: " << i << std::endl << std::endl;
    }

private:
    FunctionObject fun_;
};

#endif

