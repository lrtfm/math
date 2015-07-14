/*
 * Mvector.hpp
 *
 * 2014-12-23  1:02:47
 *
 * YangZongze yangzongze@gmail.com
 */

#ifndef MVECTOR_HPP__
#define MVECTOR_HPP__

#include "Mmatrix.hpp"
#include "Mcommon.hpp"
#include <cmath>
#include <string>

class Mvector : public Mmatrix {
public:
    Mvector() {}

    Mvector(const Mvector &o):Mmatrix(o) {}

    Mvector(const Mmatrix &o):Mmatrix(o) { 
        setRowCol(o.getRow() * o.getCol(), 1);
    }

    Mvector(int d) : Mmatrix(d, 1) {} 

    void setDim(int d) { setRowCol(d, 1); }
    int getDim() const { return getRow(); }

    Mvector delta(int i, double h) const {
        Mvector ret(*this);
        ret[i] += h;
        return ret;
    }

    Mvector delta(int i, double hi, int j, double hj) const {
        Mvector ret(*this);
        ret[i] += hi;
        ret[j] += hj;
        return ret;
    }
    double getNorm() const {
        Mmatrix r(1);
        r = transform(*this) * (*this);
        return sqrt(r(0, 0));
    }

    double & operator[](int i) {
        return (*this)(i,0);
    }

    const double & operator[](int i) const {
        return (*this)(i, 0);
    }

    void normalize() {
        double max = 0;
        double t = 0;
        for (int i = 0; i < getDim(); ++i) {
            t = fabs((*this)(i,0));
            if (t > max) {
                max = t;
            }
        }

        if (t > MC::epsilon) {
            for (int i = 0; i < getDim(); ++i) {
                (*this)(i,0) = (*this)(i,0)/max;
            }
        }

    }

};

#endif

