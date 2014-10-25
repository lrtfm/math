#include "fdm.hpp"
#include <iomanip>

FDM::FDM()
{}

FDM::FDM(double left, double right, double mu,
        InitialBoundaryCond leftBoundaryCond, 
        InitialBoundaryCond rightBoundaryCond,
        InitialBoundaryCond initialValueCond,
        SourceTerm sourceTerm) 
    : left_(left), right_(right), mu_(mu),
      leftBoundaryCond_(leftBoundaryCond),
      rightBoundaryCond_(rightBoundaryCond),
      initialValueCond_(initialValueCond),
      sourceTerm_(sourceTerm)
{}

int FDM::solver()
{
    return 0;
}

int FDM::solver_FTCS(int M, double stepT, std::vector<double> timeNeedPrint, int N)
{
    std::vector<double> u1(M + 1), u2(M + 1);
    std::vector<double> *uOld = &u1;
    std::vector<double> *uNew = &u2;
    std::vector<double> *uTemp;

    double stepX = (right_ - left_) / M;

    for (int i = 0; i <= M; ++i) {
        uOld->at(i) = initialValueCond_(i * stepX);
    }

    std::cout << "++++++++++++++++++++++++++++++++++ Begin output +++++++++++++++++++++++++++++++++++++" << std::endl;
    print(0.0, *uOld);
    int n = 1;
    bool stop = false;
    while (!stop) {
        FTCS_scheme(*uOld, stepX, stepT, n, *uNew);

        double currentT = n * stepT;

        if (N == 0 && needPrint(stepT, currentT, timeNeedPrint)) {
            print(currentT, *uNew);
        } else if (N != 0){
            print(currentT, *uNew);
        }
        clearTime(stepT, currentT, timeNeedPrint);

        if ((N == 0 && needStop(timeNeedPrint)) || ( N != 0 && n >= N))
            stop = true;

        uTemp = uOld;
        uOld = uNew;
        uNew = uTemp;
        n++;
    }
    std::cout << "++++++++++++++++++++++++++++++++++  End  output +++++++++++++++++++++++++++++++++++++" << std::endl;

    return 0;
}

int FDM::FTCS_scheme(std::vector<double> &uOld, double stepX, double stepT, int n, std::vector<double> &uNew)
{
    int M = uOld.size() - 1;
    double r = mu_ * stepT / (stepX * stepX);
    for (int k = 1; k < M; ++k) {
        uNew[k] = uOld[k] + r * centeredSecondDiff(uOld, k) + 
            stepT * sourceTerm_(k*stepX, n*stepT);
    }
    uNew[0] = leftBoundaryCond_(n*stepT);
    uNew[M] = rightBoundaryCond_(n*stepT);
}

double FDM::centeredSecondDiff(std::vector<double> &u, int k)
{
    return u[k-1] - 2*u[k] + u[k+1];
}

bool FDM::needPrint(double stepT, double currentTime, std::vector<double> &outTime)
{
    for(int i = 0; i < outTime.size(); ++i) {
        if (outTime[i] < currentTime + stepT/4.0 && outTime[i] > currentTime - stepT/4.0) {
            return true;
        }
    }
    return false;
}

void FDM::print(double currentTime, std::vector<double> & u)
{
    std::cout << "Time = " << currentTime << ":" << std::endl;
    for (int i = 0; i < u.size(); ++i) {
        std::cout << std::setw(12) << std::setprecision(6) << u[i] << "\t";
    }
    std::cout << std::endl;
}

void FDM::clearTime(double stepT, double currentTime, std::vector<double> &outTime)
{
    for(std::vector<double>::iterator it = outTime.begin(); it != outTime.end(); ) {
        if (*it < currentTime + 3*stepT/4.0) {
            it = outTime.erase(it);
        }
        else {
            ++it;
        }
    }
}

bool FDM::needStop(std::vector<double> &outTime)
{
    return outTime.empty();
}
