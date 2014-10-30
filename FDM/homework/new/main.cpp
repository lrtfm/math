#include "first_solver.hpp"


double PI = 3.1415926;
double initialValueCond_121(double x) { return sin(2*PI*x); }
double leftBoundaryCond_121(double t) { return 0.0; }
double rightBoundaryCond_121(double t) { return 0.0; }
double sourceTerm_121(double x, double t) { return 0.0; }

void problem_121()
{
    First_solver problem;
    problem.setEquation(0, 1.0, 1.0/6, 
            sourceTerm_121, initialValueCond_121,
            leftBoundaryCond_121, rightBoundaryCond_121);

    problem.setFile("problem_1.2.1.txt");
    problem.setInfo(" problem 1.2.1 ");

    std::vector<double> time;
    time.push_back(0.06); time.push_back(0.1); time.push_back(0.9); time.push_back(50);
    problem.setStepAndTime(10, 0.02, time);
    problem.solver();

    std::vector<double>time2;
    time2.push_back(50.0);
    problem.setStepAndTime(10, 0.01, time2);
    problem.solver();
    problem.setStepAndTime(10, 0.02, time2);
    problem.solver();
    problem.setStepAndTime(10, 0.025, time2);
    problem.solver();
    problem.setStepAndTime(10, 0.04, time2);
    problem.solver();
}

int main()
{
    problem_121();
    return 0;
}
