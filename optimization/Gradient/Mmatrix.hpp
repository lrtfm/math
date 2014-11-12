#ifndef __MMATRIX_HPP__
#define __MMATRIX_HPP__

#include <iostream>
#include <vector>

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

    Mmatrix(const Mmatrix & o):m_(o.m_), n_(o.n_), data_(o.data_)
    {
    }

    int getRow() const
    {
        return m_;
    }

    int getCol() const
    {
        return n_;
    }

    void setRowCol(int m, int n)
    {
        if (m_ * n_ != m * n)
            data_.resize(m_ * n_);

        m_ = m;
        n_ = n;
    }

    double & operator()(int i, int j)
    {
        return data_[i * n_ + j];
    }

    const double & operator()(int i, int j) const 
    {
        return data_[i * n_ + j];
    }

    friend std::ostream & operator<<(std::ostream &o , const Mmatrix &a); 
    friend Mmatrix transform(const Mmatrix & o);
    friend Mmatrix operator+(const Mmatrix &a, const Mmatrix &b);
    friend Mmatrix operator-(const Mmatrix &a, const Mmatrix &b);
    friend Mmatrix operator*(const Mmatrix &a, const Mmatrix &b);
    friend Mmatrix operator/(const Mmatrix &a, const Mmatrix &b);
    friend Mmatrix operator/(const Mmatrix &x, double alpha);
    friend Mmatrix operator/(double alpha, const Mmatrix &x);
    friend Mmatrix operator*(double alpha, const Mmatrix &x);

    static Mmatrix E(int n) {
        Mmatrix r(n);
        for (int i = 0; i < n; i++) {
            r(i, i) = 1;
        }
        return r;
    }

private:
    int m_;
    int n_;
    std::vector<double> data_;
};

class Mdouble : public Mmatrix
{
public:
    Mdouble():Mmatrix(1)
    {}

    Mdouble(double a):Mmatrix(1)
    {
        (*this)(0,0) = a;
    }
    double value()
    {
        return (*this)(0,0);
    }
};

Mmatrix transform(const Mmatrix & o)
{
    Mmatrix r(o.n_, o.m_);
    for (int i = 0; i < o.n_; ++i) {
        for (int j = 0; j < o.m_; ++j) {
            r(i, j) = o(j, i);
        }
    }
    return r;
}

std::ostream & operator<<(std::ostream &o , const Mmatrix &a)
{
    o << "[";
    for (int i = 0; i < a.m_; ++i) {
        if (i != 0) {
            o << "; "; // std::endl;
        }
        for (int j = 0; j < a.n_; ++j) {
            if (j != 0) {
                o << ", ";
            }
            o << a(i, j) ;
        }
    }
    o << "]";
}
Mmatrix operator+(const Mmatrix &a, const Mmatrix &b)
{
    Mmatrix r = a;
    if (a.m_ != b.m_ || a.n_ != b.n_)
        return r; //error

    for (int i = 0; i < a.m_; ++i) {
        for (int j = 0; j < a.n_; ++j) {
            r(i, j) += b(i, j);
        }
    }

    return r;
}
Mmatrix operator-(const Mmatrix &a, const Mmatrix &b)
{
    Mmatrix r = a;
    if (a.m_ != b.m_ || a.n_ != b.n_)
        return r; //error

    for (int i = 0; i < a.m_; ++i) {
        for (int j = 0; j < a.n_; ++j) {
            r(i, j) -= b(i, j);
        }
    }

    return r;
}
Mmatrix operator*(const Mmatrix &a, const Mmatrix &b)
{
    Mmatrix r(a.m_, b.n_);

    if (a.n_ != b.m_)
        return r; // error

    for (int i = 0; i < a.m_; ++i) {
        for (int j = 0; j < b.n_; ++j) {
            for (int k = 0; k < a.n_; ++k) {
                r(i, j) += a(i,k) * b(k, j);
            }
        }
    }
    return r;
}
Mmatrix operator*(double alpha, const Mmatrix &x)
{
    Mmatrix r = x;

    for (int i = 0; i < x.m_; ++i) {
        for (int j = 0; j < x.n_; ++j) {
            r(i, j) *= alpha;
        }
    }
    return r;
}
Mmatrix operator/(const Mmatrix &a, const Mmatrix &b)
{
    if (a.m_ == 1 && a.n_ == 1) {
        return a(0, 0) / b;
    }
    if (b.m_ == 1 && b.n_ == 1) {
        return a / b(0, 0);
    }

    // error TODO
    return a;
}

Mmatrix operator/(const Mmatrix &x, double alpha)
{
    Mmatrix r = x;
    for (int i = 0; i < x.m_; ++i) {
        for (int j = 0; j < x.n_; ++j) {
            r(i, j) = r(i, j) / alpha;
        }
    }
    return r;
}
Mmatrix operator/(double alpha, const Mmatrix &x)
{
    Mmatrix r = x;
    for (int i = 0; i < x.m_; ++i) {
        for (int j = 0; j < x.n_; ++j) {
            r(i, j) = alpha / r(i, j); 
        }
    }
    return r;
}

#endif
