/* neumann_solver.hpp
 *
 */

#include "fdm_solver.hpp"

class Neumann : public FDM
{
public:
    void setEquation(double l, double r, double mu,
            SourceTerm st, BoundaryCond initial,
            BoundaryCond lb, BoundaryCond rb);

    void setStepAndTime(int M, double stepT, std::vector<double> & times);

    virtual void scheme(int n, std::vector<double> &uOld, std::vector<double> &uNew);
};

class NeumannS : public Neumann
{
    virtual void scheme(int n, std::vector<double> &uOld, std::vector<double> &uNew);
};

