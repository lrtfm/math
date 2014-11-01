/* leapforg.hpp
 */
#include "fdm_solver.hpp"

class Leapforg : public FDM
{
public:
    void setEquation(double l, double r, double mu,
            SourceTerm st, BoundaryCond initial,
            BoundaryCond lb, BoundaryCond rb);

    void setReal(SourceTerm real);
    void setStepAndTime(int M, double stepT, std::vector<double> & times);
    virtual void solver();

protected:
    virtual void scheme(int n, std::vector<double> &uOld, std::vector<double> &uMid, std::vector<double> &uNew);
    void init(std::vector<double> &uNew, std::vector<double> &uMid);

private:
    SourceTerm real_;
};

