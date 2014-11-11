#ifndef __OneDimSearch_hpp__
#define __OneDimSearch_hpp__

#include "Mfunction.hpp"

namespace MSP {
    void advanceAndRetreat(FunctionObject &fun, double x, double *a, double *b)
    {
        double t = 2;
        double h = 0.1;
        if (fun(x + h) > fun(x)) {
            h = -h;
        }

        while (fun(x + h) < fun(x)) {
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
    double goldSection(FunctionObject &fun, double a, double b, double e)
    {
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
