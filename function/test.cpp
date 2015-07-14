/*
 * Mrpn.cpp
 *
 * YangZongze yangzongze@gmail.com
 */

#include "Mfunction.hpp"
#include "Mtoken.hpp"
#include <cstdlib>

#include <map>


typedef std::map<std::string, double> Workspace;


int main()
{
    char dot = '.';
    char underLine = '_';
    std::string blank(" \n\t");
    std::string num("0123456789");
    std::string alphabet("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    TokenRule blankRule(blank);
    TokenRule keyRule(alphabet + num + underLine, alphabet + underLine);
    TokenRule numRule(num + dot, num, num);
    TokenRule sepRule(blank + ",");

    std::vector<TokenRule> numRuleVect(1, numRule);
    std::vector<TokenRule> keyRuleVect(1, keyRule);
    TokenProcess numProcess(sepRule, numRuleVect);
    TokenProcess keyProcess(sepRule, keyRuleVect);

    Workspace workspace;

    // char name[256];
    std::string name;
    std::string var;
    std::vector<double> v;
    std::string token;
    std::string valueStr;
    while (1) {
        name.clear();
        std::cout << ">> " ;
        std::getline(std::cin, name);
        if (name == "exit" || name == "#") {
            break;
        } 
        if (name.size() == 0 || blankRule.isMatchRule(name)) {
            continue;
        }
        std::size_t found = name.find('=');
        size_t index = 0;
        if (std::string::npos != found) {

            // before =
            try {
                keyProcess.getToken(name, index, token);
            } catch (UnknowToken &t) {
                std::cout << t.info() << std::endl;
                continue;
            }

            // after =
            try {
                index = 0;
                numProcess.getToken(name.substr(found + 1), index, valueStr);
                workspace.insert(std::make_pair(token, atof(valueStr.c_str())));
            } catch (UnknowToken &t) {
                try {
                    index = 0;
                    keyProcess.getToken(name.substr(found + 1), index, valueStr);
                    if (workspace.end() != workspace.find(valueStr)) {
                        workspace.insert(std::make_pair(token, workspace[valueStr]));
                    }
                    else {
                        std::cout << "Unknow Token: " << valueStr << std::endl;
                        continue;
                    }
                } catch (UnknowToken &t) {
                    std::cout << t.info() << std::endl;
                    continue;
                }
            }
        } else {
            var.clear();
            v.clear();
            for (Workspace::iterator it = workspace.begin(); it != workspace.end(); ++it) {
                var = var + " " + it->first;
                v.push_back(it->second);
            }
            // std::cout << "var :" << var << std::endl;
            FunctionBase test(var, name);
            test.init();
            // std::cout <<"result: " << test.compute(v) <<std::endl;
            std::cout << test.compute(v) << std::endl;
        }
    }


    return 0;
}
