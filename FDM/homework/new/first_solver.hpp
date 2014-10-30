#include "fdm_solver.hpp"

class First_solver : public FDM
{
public:
    void setEquation(double l, double r, double mu,
            SourceTerm st, BoundaryCond initial,
            BoundaryCond lb, BoundaryCond rb);

    void setStepAndTime(int M, double stepT, std::vector<double> & times);

    virtual void scheme(int n, std::vector<double> &uOld, std::vector<double> &uNew);
};

