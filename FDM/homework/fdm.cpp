#include "fdm.hpp"
#include <iomanip>

FDM::FDM()
{}

// 构造函数
FDM::FDM(double left, double right, double mu, SourceTerm sourceTerm) 
    : left_(left), right_(right), mu_(mu), sourceTerm_(sourceTerm)
{  

    leftBoundaryCond_ = NULL; // a(t); leftBoundary
    leftNeumannCond_ = NULL; // 纽曼边界条件
    rightBoundaryCond_ = NULL; // b(t); rightBoundary
    rightNeumannCond_ = NULL;
    initialValueCond_ = NULL;
}

FDM::~FDM()
{
    if (file_.is_open()) {
        file_.close();
    }
}

void FDM::setFile(const char *fileName)
{
    if (file_.is_open()) {
        file_.close();
    }
    file_.open(fileName, std::ofstream::out | std::ofstream::app);
}

void FDM::setNeumannOrder(int order)
{
    neumannOrder_ = order;
}

void FDM::setLeftBoundaryCond(InitialBoundaryCond leftBoundaryCond) 
{
    leftBoundaryCond_ = leftBoundaryCond;
}

void FDM::setLeftNeumannCond(InitialBoundaryCond leftNeumannCond)
{
    leftNeumannCond_ = leftNeumannCond;
}

void FDM::setRightBoundaryCond(InitialBoundaryCond rightBoundaryCond)
{
    rightBoundaryCond_ = rightBoundaryCond;
}

void FDM::setRightNeumannCond(InitialBoundaryCond rightNeumannCond)
{
    rightNeumannCond_ = rightNeumannCond;
}

void FDM::setInitialValueCond(InitialBoundaryCond initialValueCond)
{
    initialValueCond_ = initialValueCond;
}

void FDM::setParameter(int M, double stepT)
{
    M_ = M;
    stepT_ = stepT;
    stepX_ = (right_ - left_) / M;
}
    
void FDM::initial(std::vector<double> &value)
{
    for (int i = 0; i <= M_; ++i) {
        value[i] = initialValueCond_(i * stepX_);
    }
}

int FDM::solver_FTCS(std::vector<double> timeNeedPrint)
{
    std::vector<double> uNew(M_+1), uOld(M_+1);

    initial(uNew);

    double currentT = 0;
    bool stop = false;
    for (int n = 1; stop != true; ++n) {
        uOld = uNew;
        currentT = n * stepT_;
        FTCS_scheme(n, uOld, uNew);

        print(currentT, timeNeedPrint, uNew);
        stop = isNeedStop(timeNeedPrint);
    }

    return 0;
}

int FDM::FTCS_scheme(int n, std::vector<double> &uOld, std::vector<double> &uNew)
{
    double r = mu_ * stepT_ / (stepX_ * stepX_);
    double s = mu_ * stepT_ / stepX_;
    for (int k = 1; k < M_; ++k) {
        uNew[k] = uOld[k] + r * centeredSecondDiff(uOld, k) + 
            stepT_ * sourceTerm_(k*stepX_, n*stepT_);
    }
    if (leftNeumannCond_ == NULL){
        uNew[0] = leftBoundaryCond_(n*stepT_);
    } else {
        if (neumannOrder_ == 1) {
            uNew[0] = uNew[1] - stepX_ * leftNeumannCond_(n*stepT_);
        } else {
            uNew[0] = uOld[0] + 2*r*(uOld[1] - uOld[0]) - 2*s*leftNeumannCond_((n-1)*stepT_);
        }
    }
    if (rightNeumannCond_ == NULL) {
        uNew[M_] = rightBoundaryCond_(n*stepT_);
    } else {
        if (neumannOrder_ == 1) {
            uNew[M_] = uNew[M_-1] + stepX_ * rightNeumannCond_(n*stepT_);
        } else {
            uNew[M_] = uOld[M_] + 2*r*(uOld[M_-1] - uOld[M_]) + 2*s*rightNeumannCond_((n-1)*stepT_);
        }
    }
}

double FDM::centeredSecondDiff(std::vector<double> &u, int k)
{
    return u[k-1] - 2*u[k] + u[k+1];
}

// 需要优化 功能太杂
void FDM::print(double currentTime, std::vector<double> & timeVect, std::vector<double> &u)
{
    for(std::vector<double>::iterator it = timeVect.begin(); it != timeVect.end(); ) {
        if (*it > currentTime - stepT_/4.0 && *it < currentTime + stepT_/4.0) {
            file_ << "StepT :" << std::setw(6) << std::setprecision(3) << stepT_ ;
            file_ << ",Time :" << std::setw(6) << std::setprecision(3) << currentTime << "->";
            for (int i = 0; i < u.size(); ++i) {
                file_ << std::setw(10) << std::setprecision(6) << u[i] << "\t";
            }
            file_ << std::endl;
            it = timeVect.erase(it);
        }
        else if (*it < currentTime + 3*stepT_/4.0) {
            it = timeVect.erase(it);
        }
        else {
            ++it;
        }
    }
}

bool FDM::isNeedStop(std::vector<double> &outTime)
{
    return outTime.empty();
}
