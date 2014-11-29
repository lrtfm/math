/*
 * Mrpn.cpp
 *
 * YangZongze yangzongze@gmail.com
 */

#include "Mrpn.hpp"
#include "Mtoken.hpp"

// std::string num("0123456789");
// std::string alpha( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
// TokenRule blankRule(std::string(" \n\t"));
// TokenRule numberRule(num + ".",num);
// TokenRule keyRule(alpha + num + "_", alpha + "_");

int main()
{
//     TokenProcess process;
//     process.setBlankRule(blankRule);
//     process.addTokenRule(numberRule);
//     process.addTokenRule(keyRule);
    char name[256];
    char var[256];
    std::string token;
    while (1) {
        std::cout << std::endl;
        std::cout << "Please input var:" << std::endl;
        std::cin.getline(var, 256);
        std::cout << "Please input formual:" << std::endl;
        std::cin.getline(name, 256);
        if (std::cin.eof()) {
            break;
        }
//         size_t i = 0;
//         try {
//             while (process.getToken(name, i, token)) {
//                 std::cout << "\t" << token;
//             }
//             std::cout << std::endl;
//         }
//         catch (UnknowToken & e) {
//             std::cout << std::endl << e.info() << std::endl;
//         }

        FunctionBase test(var, name);
        test.print();
    }
    return 0;
}
