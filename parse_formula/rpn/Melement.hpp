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
    ET_OPERATOR,   // +-*/^
    ET_VARIATION,  // x y z   TODO
    ET_CONSTNUM   // 1 2 3 
};

class Element {
public:
    Element(){}
    Element(const char *str)
        :str_(str), type_(ET_OPERATOR), priority_(0) {}
    Element(const char *str, int priority)
        :str_(str), type_(ET_OPERATOR), priority_(priority) {}
    Element(const char *str, ElementType type, int priority)
        :str_(str), type_(type), priority_(priority) {}
    Element(const std::string &str, ElementType type, int priority)
        :str_(str), type_(type), priority_(priority) {}

    bool isOp() { 
        return type_ == ET_OPERATOR;
    }
    ElementType getType() {
        return type_;
    }
    bool operator==(const Element o) {
        return (type_ == o.type_ 
                && priority_ == o.priority_ && str_ == o.str_);
    }
    bool operator<=(const Element o) {
        return (priority_ <= o.priority_);
    }

public:
    std::string str_;
private:
    ElementType type_;
    int priority_;
};

typedef std::map<std::string, Element> KeyElementMap;

extern std::string END_NAME;
extern Element Left_B;
extern Element Seprate;
extern Element Right_B;
extern Element Left_B_I;
extern const KeyElementMap systemKeyEleMap;

#endif
