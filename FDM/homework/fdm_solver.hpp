/* fdm_solver.hpp
 *
 */
#ifndef __FDM_SOLVER_HPP__
#define __FDM_SOLVER_HPP__

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

typedef double (*BoundaryCond)(double);
typedef double (*SourceTerm)(double, double);

class FDM {
public:
    FDM();
    virtual ~FDM();

    void setMu(double mu);
    void setInterval(double l, double r);
    void setSourceTerm(SourceTerm st);
    void setInitialCond(BoundaryCond initial);
    void setBoundaryCond(double lc, double lnc, BoundaryCond lb,  
                         double rc, double rnc, BoundaryCond rb);

    void setFile(const char *file_name);
    void setInfo(const char *info);

    void setStep(int M, double stepT);
    void setTime(std::vector<double> & times);
    virtual void solver();
    virtual void init(std::vector<double> & u);
    virtual void scheme(int n, std::vector<double> & uOld, std::vector<double> & uNew);
    
protected:

    void print(double currentTime, std::vector<double> & u);
    bool isNeedPrint(double currentTime);
    bool isNeedStop(double currentTime);

    void prePrint();
    void postPrint();

private:

protected:
    double mu_;
    double l_, r_; 

    double lc_, rc_;
    double lnc_, rnc_;
    BoundaryCond lb_, rb_; 
    BoundaryCond initial_;  
    SourceTerm st_;  

    std::ofstream file_;

    std::string info_;
    int M_;
    double stepX_, stepT_;
    std::vector<double> time_;
};

#endif
