/*
 * Melement.hpp
 *
 * YangZongze yangzongze@gmail.com
 */

#ifndef MELEMENT_HPP__
#define MELEMENT_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <map>

enum ElementType {
    ET_IVALID,
    ET_OPERATOR,   // +-*/^
    ET_VARIATION,  // x y z   TODO
    ET_CONSTNUM   // 1 2 3 
};

class Element {
public:
    Element();
    Element(const char *str, ElementType type, int priority);
    Element(const std::string &str, ElementType type, int priority);

    bool isOp(); 
    bool isValid();
    void setName(std::string & name);     
    std::string getName();
    ElementType getType(); 
    bool operator==(const Element o);
    bool operator<=(const Element o);

public:
    std::string str_;
private:
    ElementType type_;
    int priority_;
};

#endif
