#include "Mmatrix.hpp"
#include "Mvector.hpp"
#include <iostream>

int main() {
    Mmatrix A(2, 3);
    Mmatrix B(3, 2);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3; 
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;

    B(0, 0) = 1; B(0, 1) = 2;
    B(1, 0) = 3; B(1, 1) = 4;
    B(2, 0) = 5; B(2, 1) = 6;

    Mmatrix C;

    std::cout << "A = " << A << std::endl;
    std::cout << "B = " << B << std::endl;

    C = A - A;
    std::cout << "C = A - A" << std::endl;
    std::cout << "C = " << C << std::endl;

    C = B + B;
    std::cout << "C = B + B" << std::endl;
    std::cout << "C = " << C << std::endl;

    C = A*B;
    std::cout << "C = A*B" << std::endl;
    std::cout << "C = " << C << std::endl;

    C = 2*A;
    std::cout << "C = 2 * A" << std::endl;
    std::cout << "C = " << C << std::endl;

    C = transform(A) * transform(B);
    std::cout << "C = A' * B'" << std::endl;
    std::cout << "C = " << C << std::endl;

    C = transform(A) / 0.5;
    std::cout << "C = A' * B'" << std::endl;
    std::cout << "C = " << C << std::endl;

    C = A / 2;
    std::cout << "C = A / 2" << std::endl;
    std::cout << "C = " << C << std::endl;
    C = 2 / A;
    std::cout << "C = 2 / A" << std::endl;
    std::cout << "C = " << C << std::endl;

    Mmatrix D(1,1);
    D(0, 0) = 3;
    std::cout << "D = " << D << std::endl;

    C = D / A;
    std::cout << "C = D / A" << std::endl;
    std::cout << "C = " << C << std::endl;
    C = A / D;
    std::cout << "C = A / D" << std::endl;
    std::cout << "C = " << C << std::endl;

    Mvector x(3);
    Mvector y(3);
    x[0] = 1; x[1] = 2; x[2] = 3;
    y[0] = 4; y[1] = 5; y[2] = 6;

    Mvector z;
    z = x + y;
    std::cout << "z = x + y" << std::endl;
    std::cout << "z = " << z << std::endl;

    z = x - y;
    std::cout << "z = x - y" << std::endl;
    std::cout << "z = " << z << std::endl;

    C = x * transform(y);
    std::cout << "C = x * y'" << std::endl;
    std::cout << "C = " << C << std::endl;

    C = transform(x) * y;
    std::cout << "C = x' * y" << std::endl;
    std::cout << "C = " << C << std::endl;

    Mvector c;
    c = x / 2;
    std::cout << "c = x/ 2" << std::endl;
    std::cout << "c = " << c << std::endl;

    c = 2 / x;
    std::cout << "c = 2/ x" << std::endl;
    std::cout << "c = " << c << std::endl;

    Mdouble a = 2;
    std::cout << "a = " << a << std::endl;

    return 0;
}

