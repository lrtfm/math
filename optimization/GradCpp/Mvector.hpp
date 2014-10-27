#ifndef __MVECTOR_HPP__
#define __MVECTOR_HPP__

#include <vector>
#include <string>
#include <iostream>

class Mvector
{
public:
    Mvector() : d_(0)
    {}

    Mvector(const Mvector &o) : d_(o.d_), v_(o.v_)
    {}

    Mvector(int d) : d_(d)
    {
        v_.resize(d);
    }
    
    Mvector(const std::vector<double> &v) : d_(v.size()), v_(v)
    {}

    int getDim() const {
        return d_;
    }

    Mvector delta(int i, double h) const {
        Mvector ret(*this);
        ret.v_[i] += h;
        return ret;
    }

    double getNorm() const {
        double norm = 0;
        for (int i = 0; i < d_; ++i) {
            norm += v_[i] * v_[i];
        }
        return norm;
    }

    double & operator[](int i) {
        return v_[i];
    }

    const double & operator[](int i) const {
        return v_[i];
    }

    void print() const {
        for (int i = 0; i < d_; ++i) {
            std::cout << v_[i] << "\t" ;
        }
        std::cout << std::endl;

    }

    void print(std::string s) const {
        std::cout << s << " : \t" ; // << std::endl;
        for (int i = 0; i < d_; ++i) {
            std::cout << v_[i] << "\t" ;
        }
        std::cout << std::endl;

    }

    // 向量加法
    friend Mvector operator+(const Mvector &a, const Mvector &b);
    // 向量减法
    friend Mvector operator-(const Mvector &a, const Mvector &b);
    // 向量数乘运算
    friend Mvector operator*(double alpha, const Mvector &x);

private:
    int d_;
    std::vector<double> v_;
};
       

Mvector operator+(const Mvector &a, const Mvector &b) {
    Mvector ret(a.getDim());
    if (a.d_ == b.d_) {
        for (int i = 0; i < a.d_; ++i) {
            ret.v_[i] = a.v_[i] + b.v_[i];
        }
    }

    return ret;
}

Mvector operator-(const Mvector &a, const Mvector &b) {
    Mvector ret(a.getDim());
    if (a.d_ == b.d_) {
        for (int i = 0; i < a.d_; ++i) {
            ret.v_[i] = a.v_[i] - b.v_[i];
        }
    }

    return ret;
}

Mvector operator*(double alpha, const Mvector &x)
{
    Mvector ret(x.getDim());
    for (int i = 0; i < x.d_; ++i) {
        ret.v_[i] = alpha * x.v_[i];
    }
    return ret;
}

#endif

