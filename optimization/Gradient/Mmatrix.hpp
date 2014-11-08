#ifndef __MMATRIX_HPP__
#define __MMATRIX_HPP__

#include "Mvector.hpp"

class Mmatrix{
public:
    Mmatrix():m_(0),n_(0) {}
    Mmatrix(int n):m_(n),n_(n)
    {
        data_ = std::vector<double>(m_*n_, 0.0);
    }
    Mmatrix(int m, int n):m_(m), n_(n)
    {
        data_ = std::vector<double>(m_*n_, 0.0);
    }

    double & operator()(int i, int j)
    {
        return data_[i * n_ + j];
    }

private:
    int m_;
    int n_;
    std::vector<double> data_;
};
#endif
