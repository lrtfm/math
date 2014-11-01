/* leapforg.cpp
 */

#include "leapforg.hpp"

void Leapforg::setEquation(double l, double r, double mu,
            SourceTerm st, BoundaryCond initial,
            BoundaryCond lb, BoundaryCond rb)
{
    setInterval(l, r);
    setMu(mu);
    setSourceTerm(st);
    setInitialCond(initial);
    setBoundaryCond(1.0, 0.0, lb, 1.0, 0.0, rb);
}

void Leapforg::setStepAndTime(int M, double stepT, std::vector<double> & times)
{
    setStep(M, stepT);
    setTime(times);
}

void Leapforg::setReal(SourceTerm real)
{
    real_ = real;
}


void Leapforg::scheme(int n, std::vector<double> &uOld,  std::vector<double> &uMid, std::vector<double> &uNew)
{
    double r = mu_ * stepT_ / (stepX_ * stepX_);
    for (int k = 1; k < M_; ++k) {
        uNew[k] = uOld[k] + r * (uMid[k+1] - 2 * uMid[k] + uMid[k-1]) + 
            stepT_ * st_(k*stepX_, n*stepT_);
    }

    uNew[0] = lb_(n*stepT_);
    uNew[M_] = rb_(n*stepT_);
}

void Leapforg::init(std::vector<double> &uNew, std::vector<double> &uMid)
{
    for (int i = 0; i <= M_; ++i) {
        uNew[i] = initial_(i * stepX_);
    }
    uMid = uNew;
    for (int i = 0; i <= M_; ++i) {
        uNew[i] = real_(i * stepX_, stepT_);
    }
}

void Leapforg::solver()
{
    std::vector<double> uNew(M_+1), uMid(M_+1), uOld(M_+1);

    init(uNew, uMid);

    prePrint();
    double currentT = 0;
    bool stop = false;
    for (int n = 1; stop != true; ++n) {
        uOld = uNew;
        currentT = n * stepT_;
        scheme(n, uOld, uMid, uNew);

        if(isNeedPrint(currentT)) {
            print(currentT, uNew);
        }
        stop = isNeedStop(currentT);
    }
    postPrint();
}
