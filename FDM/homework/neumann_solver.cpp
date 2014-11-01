/* neumann_solver.cpp
 *
 */
#include "neumann_solver.hpp"

void Neumann::setEquation(double l, double r, double mu,
            SourceTerm st, BoundaryCond initial,
            BoundaryCond lb, BoundaryCond rb)
{
    setInterval(l, r);
    setMu(mu);
    setSourceTerm(st);
    setInitialCond(initial);
    setBoundaryCond(0.0, 1.0, lb, 1.0, 0.0, rb);
}

void Neumann::setStepAndTime(int M, double stepT, std::vector<double> & times)
{
    setStep(M, stepT);
    setTime(times);
}


void Neumann::scheme(int n, std::vector<double> &uOld, std::vector<double> &uNew)
{
    double r = mu_ * stepT_ / (stepX_ * stepX_);
    for (int k = 1; k < M_; ++k) {
        uNew[k] = uOld[k] + r * (uOld[k+1] - 2 * uOld[k] + uOld[k-1]) + 
            stepT_ * st_(k*stepX_, n*stepT_);
    }

    uNew[0] = uNew[1] - stepX_ * lb_(n*stepT_);
    uNew[M_] = rb_(n*stepT_);
}

void NeumannS::scheme(int n, std::vector<double> &uOld, std::vector<double> &uNew)
{
    double r = mu_ * stepT_ / (stepX_ * stepX_);
    double s = mu_ * stepT_ / stepX_;
    for (int k = 1; k < M_; ++k) {
        uNew[k] = uOld[k] + r * (uOld[k+1] - 2 * uOld[k] + uOld[k-1]) + 
            stepT_ * st_(k*stepX_, n*stepT_);
    }

    uNew[0] = uOld[0] + 2*r*(uOld[1] - uOld[0]) - 2*s*lb_((n-1)*stepT_);
    uNew[M_] = rb_(n*stepT_);
}
