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
    FDM fdm(0, 1, 1.0/6.0, sourceTerm_121);
    fdm.setLeftBoundaryCond(leftBoundaryCond_121);
    fdm.setRightBoundaryCond(rightBoundaryCond_121);
    fdm.setInitialValueCond(initialValueCond_121);

    //               M    stepT
    fdm.setParameter(10, 0.02);

    fdm.setFile("problem_1.2.1_1.txt");
    std::vector<double> time;
    time.push_back(0.06);
    time.push_back(0.1);
    time.push_back(0.9);
    time.push_back(50);
    fdm.solver_FTCS(time);


    fdm.setFile("problem_1.2.1_2.txt");
    std::vector<double>time2;
    time2.push_back(50.0);
    fdm.setParameter(10, 0.01);
    fdm.solver_FTCS(time2);
    fdm.setParameter(10, 0.02);
    fdm.solver_FTCS(time2);
    fdm.setParameter(10, 0.025);
    fdm.solver_FTCS(time2);
    fdm.setParameter(10, 0.04);
    fdm.solver_FTCS(time2);
    fdm.setParameter(10, 0.05);
    fdm.solver_FTCS(time2);
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
    FDM fdm(0.0, 1.0, 0.1, sourceTerm_158);
    fdm.setLeftBoundaryCond(leftBoundaryCond_158);
    fdm.setRightBoundaryCond(rightBoundaryCond_158);
    fdm.setInitialValueCond(initialValueCond_158);

    fdm.setFile("problem_1.5.8.txt");
                  // M   stepT
    fdm.setParameter(10, 0.1);
    std::vector<double> time;
    for (int i = 0; i < 20; ++i) 
        time.push_back(0.1 * (i + 1));

    //              M   stepT
    fdm.solver_FTCS(time);
}
    
int main()
{
    problem_121();
    problem_158();

    return 0;
}
