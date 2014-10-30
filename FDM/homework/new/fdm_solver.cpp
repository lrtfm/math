#include "fdm_solver.hpp"

FDM::FDM()
{}

FDM::~FDM()
{
    if (file_.is_open()) {
        file_.close();
    }
}

void FDM::setMu(double mu)
{
    mu_ = mu;
}

void FDM::setInterval(double l, double r)
{
    l_ = l; r_ = r;
}

void FDM::setSourceTerm(SourceTerm st)
{
    st_ = st;
}

void FDM::setInitialCond(BoundaryCond initial)
{
    initial_ = initial;
}

// lc * u + lnc * u_x = lb;
void FDM::setBoundaryCond(double lc, double lnc, BoundaryCond lb,  
        double rc, double rnc, BoundaryCond rb)
{
    lc_ = lc; lnc_ = lnc; lb_ = lb; 
    rc_ = rc; rnc_ = rnc; rb_ = rb;
}

void FDM::setFile(const char *fileName)
{
    if (file_.is_open()) {
        file_.close();
    }
    file_.open(fileName, std::ofstream::out | std::ofstream::app);
}

void FDM::setInfo(const char *info)
{
    info_ = info;
}

void FDM::setStep(int M, double stepT)
{
    M_ = M;
    stepT_ = stepT;
    stepX_ = (r_ - l_)/M;
}

void FDM::setTime(std::vector<double> & times)
{
    time_ = times;
    sort(time_.begin(), time_.end());
}


void FDM::print(double currentTime, std::vector<double> & u)
{
    file_ << "T " << currentTime << ":";
    for (int i = 0; i < u.size(); ++i) {
        file_ << std::setw(8) << std::setprecision(4) << u[i] << "\t";
    }
    file_ << std::endl;
}

bool FDM::isNeedPrint(double currentTime)
{
    double e = stepT_ / 10.0;
    for (std::vector<double>::iterator it = time_.begin(); it != time_.end(); ++it) {
        if (*it < currentTime + e && *it > currentTime - e) {
            return true;
        }
    }
    return false;
}

bool FDM::isNeedStop(double currentTime)
{
    if (currentTime > time_[time_.size() - 1]) {
        return true;
    }
    return false;
}

void FDM::prePrint()
{
    file_ << "############## Begin  " << info_ << "h=" << stepX_ << " \\delta t=" << stepT_ << "  ############" << std::endl;
}

void FDM::postPrint()
{
    // file_ << "############## End    " << info_ << " h " << stepX_ << " t " << stepT_ << "  ############" << std::endl;
}

void FDM::solver()
{
    std::vector<double> uNew(M_+1), uOld(M_+1);

    init(uNew);

    prePrint();
    double currentT = 0;
    bool stop = false;
    for (int n = 1; stop != true; ++n) {
        uOld = uNew;
        currentT = n * stepT_;
        scheme(n, uOld, uNew);

        if(isNeedPrint(currentT)) {
            print(currentT, uNew);
        }
        stop = isNeedStop(currentT);
    }
    postPrint();
}

void FDM::init(std::vector<double> & u)
{
    for (int i = 0; i <= M_; ++i) {
        u[i] = initial_(i * stepX_);
    }
}

void FDM::scheme(int n, std::vector<double> & uOld, std::vector<double> & uNew)
{}
