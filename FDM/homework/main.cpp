#include "fdm.hpp"

double PI = 3.1415926;

double initialValueCond_121(double x)
{
    return sin(2*PI*x);
}

double leftBoundaryCond_121(double t)
{
    return 0.0;
}
double rightBoundaryCond_121(double t)
{
    return 0.0;
}

double sourceTerm_121(double x, double t)
{
    return 0.0;
}

void problem_121()
{
    FDM fdm(0, 1, 1.0/6.0,
            leftBoundaryCond_121,
            rightBoundaryCond_121,
            initialValueCond_121,
            sourceTerm_121);

    std::vector<double> time;
    time.push_back(0.06);
    time.push_back(0.1);
    time.push_back(0.9);
    time.push_back(50);

    fdm.solver_FTCS(10, 0.02, time, 0);

    std::vector<double>time2;
    time2.push_back(50.0);
    fdm.solver_FTCS(10, 0.01, time2, 0);
    fdm.solver_FTCS(10, 0.02, time2, 0);
    fdm.solver_FTCS(10, 0.025, time2, 0);
    fdm.solver_FTCS(10, 0.04, time2, 0);
    fdm.solver_FTCS(10, 0.05, time2, 0);
    fdm.solver_FTCS(10, 0.1, time2, 0);
}

double initialValueCond_158(double x)
{
   return x*(1 - x);
} 

double leftBoundaryCond_158(double t)
{
    return 10*sin(t);
}
double rightBoundaryCond_158(double t)
{
    return 4*sin(6*t);
}

double sourceTerm_158(double x, double t)
{
    return sin(2*PI*x)*sin(4*PI*t);
}

void problem_158()
{
    //      [0,  1]   \mu
    FDM fdm(0.0, 1.0, 0.1,
            leftBoundaryCond_158,
            rightBoundaryCond_158,
            initialValueCond_158,
            sourceTerm_158);
    //              M   stepT
    fdm.solver_FTCS(10, 0.1, std::vector<double>(), 20);
}
    
int main()
{
//    problem_158();
    problem_121();

    return 0;
}
