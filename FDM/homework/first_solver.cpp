/* first_solver.cpp
 */
#include "first_solver.hpp"

void First_solver::setEquation(double l, double r, double mu,
            SourceTerm st, BoundaryCond initial,
            BoundaryCond lb, BoundaryCond rb)
{
    setInterval(l, r);
    setMu(mu);
    setSourceTerm(st);
    setInitialCond(initial);
    setBoundaryCond(1.0, 0.0, lb, 1.0, 0.0, rb);
}

void First_solver::setStepAndTime(int M, double stepT, std::vector<double> & times)
{
    setStep(M, stepT);
    setTime(times);
}


void First_solver::scheme(int n, std::vector<double> &uOld, std::vector<double> &uNew)
{
    double r = mu_ * stepT_ / (stepX_ * stepX_);
    for (int k = 1; k < M_; ++k) {
        uNew[k] = uOld[k] + r * (uOld[k+1] - 2 * uOld[k] + uOld[k-1]) + 
            stepT_ * st_(k*stepX_, n*stepT_);
    }

    uNew[0] = lb_(n*stepT_);
    uNew[M_] = rb_(n*stepT_);
}

