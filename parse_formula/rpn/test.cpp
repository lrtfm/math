/*
 * Mrpn.cpp
 *
 * YangZongze yangzongze@gmail.com
 */

#include "Mrpn.hpp"
int main()
{
    char name[256];
    while (1) {
        std::cout << std::endl;
        std::cout << "Please input formual:" << std::endl;
        std::cin.getline(name, 256);
        if (std::cin.eof()) {
            break;
        }
        RPN test(name);
        test.change();
    }
    return 0;
}
