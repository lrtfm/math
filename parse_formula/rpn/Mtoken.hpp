/*
 * Mtoken.hpp
 *
 * YangZongze yangzongze@gmail.com
 */

#ifndef MTOKEN_HPP__
#define MTOKEN_HPP__

#include "Mexception.hpp"

#include <vector>
#include <string>
#include <set>
#include <iostream>


class UnknowToken : public ExceptionBase {
public:
    UnknowToken() : ExceptionBase("UnknowToken")
    {}
    UnknowToken(const std::string & info) : ExceptionBase("UnknowToken:" + info)
    {}
};

class TokenRule {
public:
    TokenRule()
    {}

    TokenRule(const std::string & str) 
        : middle_(str.begin(), str.end())
    {}
    TokenRule(const std::string & str, const std::string & b)
        : middle_(str.begin(), str.end()), first_(b.begin(), b.end()) 
    {}
    TokenRule(const std::string & str, const std::string & b, const std::string & e)
        : middle_(str.begin(), str.end()), first_(b.begin(), b.end()), last_(e.begin(), e.end())
    {}

    bool isMatchFirst(char c) {
        if (first_.empty()) {
            return (middle_.find(c) != middle_.end());
        }
        else {
            return (first_.find(c) != first_.end());
        }
    }
    bool isMatchMiddle(char c) {
        return (middle_.find(c) != middle_.end());
    }

    bool isMatchLast(char c) {
        if (last_.empty()) {
            return (middle_.find(c) != middle_.end());
        }
        else {
            return (last_.find(c) != last_.end());
        }
    }

    bool isMatch(char c) {
        return isMatchFirst(c) || isMatchMiddle(c) || isMatchLast(c);
    }

    bool isMatchRule(const std::string & token) {
        size_t n = token.size();
        if(n == 0) {
            return false;
        }
        if (n == 1) {
            return isMatchFirst(token[0]);
        }
        if (isMatchFirst(token[0]) && isMatchLast(token[n-1])) {
            size_t i = 1;
            while (i < n - 1 && isMatchMiddle(token[i])) {
                ++i;
            }
            if (i == n - 1) {
                return true;
            }
        }

        return false;
    }

private:
    std::set<char> middle_;
    std::set<char> first_;
    std::set<char> last_;
};

class TokenProcess {
public:
    TokenProcess() {}
    TokenProcess(TokenRule & blank, std::vector<TokenRule> & rules) 
        : blankRule_(blank), tokenRules_(rules)
    {}
    ~TokenProcess() {}

    void setBlankRule(TokenRule & rule) {
        blankRule_ = rule;
    }
    void setTokenRule(TokenRule & rule) {
        tokenRules_.resize(1);
        tokenRules_[0] = rule;
    }
    void setTokenRule(std::vector<TokenRule> & rules) {
        tokenRules_ = rules;
    }
    void addTokenRule(TokenRule & rule) {
        tokenRules_.push_back(rule);
    }
    void addTokenRule(std::vector<TokenRule> & rules) {
        size_t n = tokenRules_.size() + rules.size();
        tokenRules_.reserve(n);
        for (size_t i = 0; i < rules.size(); ++i) {
            tokenRules_.push_back(rules[i]);
        }
    }

    // 已到结尾 返回false  其他返回 true 出错抛出异常
    bool getToken(const std::string & name, size_t & index, std::string &token) {
        skipBlank(name, index);
        token = std::string("");
        if (index >= name.size()) {
            return false;
        }

        for (int j = 0; j < tokenRules_.size(); ++j) {
            size_t i = index;
            TokenRule & rule = tokenRules_[j];
            if (rule.isMatchFirst(name[i])) {
                i++;
                while (i < name.size() && rule.isMatchMiddle(name[i])) {
                    ++i;
                }

                if (i < name.size() && rule.isMatchLast(name[i])) {
                    token = name.substr(index, i - index + 1);
                    index = i + 1;
                    return true;
                } 

                // 返回寻找满足last字符的串
                i--;
                while (i >= index) {
                    if (rule.isMatchLast(name[i])) { 
                        token = name.substr(index, i - index + 1);
                        index = i + 1;
                        return true;
                    }
                    i--;
                }
            }
        }
        throw UnknowToken(name.substr(index));
        return false;
    }

    void skipBlank(const std::string & name, size_t & index) {
        while (index < name.size() && blankRule_.isMatch(name[index])) {
            index++;
        }
    }
private:
    TokenRule blankRule_;
    std::vector<TokenRule> tokenRules_;
};

#endif
