/*
 * Melement.cpp
 *
 * YangZongze yangzongze@gmail.com
 */

#include "Msys.hpp"
#include "Melement.hpp"

Element::Element() :type_(ET_CONSTNUM), priority_(-1) 
{} 
Element::Element(const char *str)
    :str_(str), type_(ET_OPERATOR), priority_(0) 
{}
Element::Element(const char *str, int priority)
    :str_(str), type_(ET_OPERATOR), priority_(priority) 
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

void Element::setName(std::string & name) 
{
    str_ = name;
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

bool NumberElementClass::isExist(std::string & name) 
{
    return MC::numRule.isMatchRule(name);
}

Element &  NumberElementClass::getElementByName(std::string & name) 
{
    element_.setName(name);
    return element_;
}

ElementClass::ElementClass() : elementMap_(NULL)
{}

ElementClass::ElementClass(KeyElementMap * elementMap)
{
    elementMap_ = elementMap;
}

void ElementClass::setElementMap(KeyElementMap * elementMap)
{
    elementMap_ = elementMap;
}

KeyElementMap* ElementClass::getElementMap()
{
    return elementMap_;
}

bool ElementClass::isExist(std::string & name) {
    if (elementMap_ == NULL) {
        return false;
    }
    return elementMap_->find(name) != elementMap_->end();
}

Element & ElementClass::getElementByName(std::string & name) {
    return elementMap_->find(name)->second;
}

ElementManager::ElementManager() {}

void ElementManager::initUserDefineElement(std::string & var)
{
    std::string token;
    size_t index = 0;
    KeyElementMap* eleMap = userDefElementS_.getElementMap();
    if (eleMap == NULL) {
        eleMap = new KeyElementMap;
        userDefElementS_.setElementMap(eleMap);
    } else {
        eleMap->clear();
    }

    while (MC::varProcess.getToken(var, index, token)) {
        eleMap->insert(
                KeyElementMap::value_type(
                    token, Element(token, ET_VARIATION, -1)));
    }
}

void ElementManager::init(std::string & var) {
    initUserDefineElement(var);
    delAllElementClass();
    addElementClass(&MC::systemElementClass);
    addElementClass(&MC::numberElementClass);
}

Element & ElementManager::getElementByName(std::string & name) 
{
    if (userDefElementS_.isExist(name)) {
        return userDefElementS_.getElementByName(name);
    }
    for (size_t i = 0; i < elementClassVect_.size(); ++i) {
        if (elementClassVect_[i]->isExist(name)) {
            return elementClassVect_[i]->getElementByName(name);
        }
    }

    throw UnknowToken(" in ElementManager::getElementByName \"" + name + "\"");
}

void ElementManager::delAllElementClass()
{
    elementClassVect_.resize(0);
}

void ElementManager::addElementClass(ElementClassBase * eleClass) 
{
    elementClassVect_.push_back(eleClass);
}

ElementManager::~ElementManager() {}
