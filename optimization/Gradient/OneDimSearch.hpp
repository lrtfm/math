#ifndef __OneDimSearch_hpp__
#define __OneDimSearch_hpp__

#include "Mcommon.hpp"
#include "Mfunction.hpp"

namespace MSP {
    void advanceAndRetreat(FunctionObject &fun, double x, double *a, double *b) {
        double t = 2;
        double h = 0.1;
        Debug("fun(x+h) =" << fun(x+h) << std::endl);
        if (fun(x + h) > fun(x)) {
            h = -h;
        }

        bool flag = false; // 如果第一次循环条件就不满足最后b的值需要调整
        Debug( "fun(x+h) = " << fun(x+h) << ", fun(x) =" << fun(x) << std::endl);
        while (fun(x + h) < fun(x)) {
            x = x + h;
            h = h * t;
            flag = true;
        }

        if (h > 0) {
            *a = x - h/t;
            *b = x + h;
        } else {
            *a = x + h;
            if (flag) {
                *b = x - h/t;
            } else {
                *b = x - h;
            }
        }
    }
#define G 0.618
    double goldSection(FunctionObject &fun, double a, double b, double e) {
        double lambda = a + (1 - G)*(b - a);
        double mu = a + G * (b - a);

        while (a - b > e || b - a > e) {
            if (fun(lambda) > fun(mu)) {
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
}

#endif
