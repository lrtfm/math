#ifndef __FDM_HPP__
#define __FDM_HPP__

#include <vector>
#include <iostream>
#include <cmath>
// 先设计为指针  可以考虑函数对象 
typedef double (*SourceTerm)(double , double);
typedef double (*InitialBoundaryCond)(double);

class FDM {
public:
    FDM();
    FDM(double left, double right, double mu,
            InitialBoundaryCond leftBoundaryCond, 
            InitialBoundaryCond rightBoundaryCond,
            InitialBoundaryCond initialValueCond,
            SourceTerm sourceTerm);

    void setMu(double mu);
    void setLeft(double left);
    void setRight(double right);
    void setLeftBoundaryCond(InitialBoundaryCond leftBoundaryCond);
    void setRightboundaryCond(InitialBoundaryCond rightBoundaryCond);
    void setInitialValueCond(InitialBoundaryCond initialValueCond);
    void setSourceTerm(SourceTerm sourceTerm);
    
    int solver();
    //int solver(double mu, int M, double stepT, std::vector<double> outputT);
    int solver_FTCS(int M, double stepT, std::vector<double> outputT, int N);

    // u_{k}^{n+1} = u_{k}^{n} + \frac{\mu \Delta t}{\Delta x^2}\delta^2u_{k}^{n} + \Delta F_{k}^{n}
    int FTCS_scheme(std::vector<double> &uOld, double stepX, double stepT, int n, std::vector<double> &uNew);
    
    bool needPrint(double stepT, double currentTime, std::vector<double> &outTime);
    void print(double currentTime, std::vector<double> & u);
    void clearTime(double stepT, double currentTime, std::vector<double> & outTime);

    bool needStop(std::vector<double> & outTime);

    double centeredSecondDiff(std::vector<double> &u, int k);

private:
    double left_, right_; // [0, 1] [left, right];
    double mu_;
    InitialBoundaryCond leftBoundaryCond_; // a(t); leftBoundary
    InitialBoundaryCond rightBoundaryCond_; // b(t); rightBoundary
    InitialBoundaryCond initialValueCond_;  // f(x);
    SourceTerm sourceTerm_;  // F(x, t); sourceTerm
};

#endif
