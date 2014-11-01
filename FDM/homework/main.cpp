/* main.cpp
 */

#include "first_solver.hpp"
#include "leapforg.hpp"
#include "neumann_solver.hpp"


double PI = 3.1415926;
double zeroCond(double t) { return 0.0; }
double zeroSourceTerm(double x, double t) { return 0.0; }

double initialValueCond_121(double x) { return sin(2*PI*x); }
void problem_121()
{
    First_solver problem;
    problem.setEquation(0, 1.0, 1.0/6, 
            zeroSourceTerm, initialValueCond_121,
            zeroCond, zeroCond);

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

double real_131(double x, double t)
{
    return exp(-4*3.1415926*3.1415926/6*t)*sin(2*3.1415926*x);
}
void problem_131()
{
    Leapforg problem;

    problem.setEquation(0, 1.0, 1.0/6, 
            zeroSourceTerm, initialValueCond_121,
            zeroCond, zeroCond);

    problem.setReal(real_131);
    problem.setFile("problem_1.3.1.txt");
    problem.setInfo(" problem 1.3.1 ");

    std::vector<double> time;
    time.push_back(0.06); time.push_back(0.1); time.push_back(0.9); time.push_back(50);
    problem.setStepAndTime(10, 0.02, time);
    problem.solver();
}

double initialValueCond_141(double x)
{
    return cos(PI*x/2.0);
} 

void problem_141()
{
    NeumannS problem;
    problem.setEquation(0.0, 1.0, 1.0, 
            zeroSourceTerm, initialValueCond_141,
            zeroCond, zeroCond);

    problem.setFile("problem_1.4.1.txt");
    problem.setInfo(" problem 1.4.1 ");

    int M = 10;
    double stepT = 0.004;
    std::vector<double> time;
    time.push_back(0.06); time.push_back(0.1); time.push_back(0.9); 
    problem.setStepAndTime(10, stepT, time);
    problem.solver();

    M = 20;
    stepT = 0.001;
    std::vector<double> time2;
    for (int i = 0; i < 50; ++i) {
        time2.push_back(i * stepT); 
    }
    problem.setInfo(" problem 1.4.2 second order ");
    problem.setStepAndTime(M, stepT, time2);
    problem.solver();
    
}

void problem_142()
{
    // first order
    Neumann problem;
    problem.setEquation(0.0, 1.0, 1.0, 
            zeroSourceTerm, initialValueCond_141,
            zeroCond, zeroCond);

    problem.setFile("problem_1.4.2.txt");
    problem.setInfo(" problem 1.4.2 first order ");

    int M = 20;
    double stepT = 0.001;
    std::vector<double> time;
    for (int i = 0; i < 50; ++i) {
        time.push_back(i * stepT); 
    }
    problem.setStepAndTime(M, stepT, time);
    problem.solver();
}

int main()
{
//    problem_121();
//    problem_131();
    problem_141();
    problem_142();
    return 0;
}
