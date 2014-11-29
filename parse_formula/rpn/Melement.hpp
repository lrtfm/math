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
    Element();
    Element(const char *str);
    Element(const char *str, int priority);
    Element(const char *str, ElementType type, int priority);
    Element(const std::string &str, ElementType type, int priority);

    bool isOp(); 
    void setName(std::string & name);     
    ElementType getType(); 
    bool operator==(const Element o);
    bool operator<=(const Element o);

public:
    std::string str_;
private:
    ElementType type_;
    int priority_;
};

typedef std::map<std::string, Element> KeyElementMap;

class ElementClassBase {
public:
    ElementClassBase() {}
    virtual bool isExist(std::string & name) = 0;
    virtual Element & getElementByName(std::string &name) = 0;

    virtual ~ElementClassBase() {}
};

class NumberElementClass : public ElementClassBase {
public:
    virtual bool isExist(std::string & name);
    virtual Element & getElementByName(std::string & name);

private:
    Element element_;
};

class ElementClass : public ElementClassBase{
public:
    ElementClass();
    ElementClass(KeyElementMap * elementMap);
    void setElementMap(KeyElementMap * elementMap);
    KeyElementMap* getElementMap();

    virtual bool isExist(std::string & name);
    virtual Element & getElementByName(std::string & name);

private:
    KeyElementMap * elementMap_;
};

class ElementManager {
public:
    ElementManager();
    void init(std::string & var);
    Element & getElementByName(std::string & name); 

    ~ElementManager();
private:

    void initUserDefineElement(std::string & var);

    void addElementClass(ElementClassBase * eleClass);
    void delAllElementClass();


private:
    ElementClass userDefElementS_;
    std::vector<ElementClassBase *> elementClassVect_;
};

#endif
