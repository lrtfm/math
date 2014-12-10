/*
 * Melement.cpp
 *
 * YangZongze yangzongze@gmail.com
 */

#include "Melement.hpp"

Element::Element() :type_(ET_IVALID)
{} 

Element::Element(const char *str, ElementType type, int priority)
    :str_(str), type_(type), priority_(priority) 
{}
Element::Element(const std::string &str, ElementType type, int priority)
    :str_(str), type_(type), priority_(priority) 
{}

bool Element::isOp() 
{ 
    return type_ == ET_OPERATOR;
}

bool Element::isValid()
{
    return type_ != ET_IVALID;
}

void Element::setName(std::string & name) 
{
    str_ = name;
}
std::string Element::getName()
{
    return str_;
}
ElementType Element::getType() 
{
    return type_;
}

bool Element::operator==(const Element o) 
{
    return (type_ == o.type_ 
            && priority_ == o.priority_ && str_ == o.str_);
}

bool Element::operator<=(const Element o) 
{
    return (priority_ <= o.priority_);
}

