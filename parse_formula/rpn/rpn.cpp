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
    Element(const char *str):str_(str), type_(ET_OPERATOR), priority_(0) {}
    Element(const char *str, int priority):str_(str), type_(ET_OPERATOR), priority_(priority) {}
    Element(const char *str, ElementType type, int priority):str_(str), type_(type), priority_(priority) {}
    Element(const std::string &str, ElementType type, int priority):str_(str), type_(type), priority_(priority) {}

    bool isOp() { return type_ == ET_OPERATOR;}
    bool operator==(const Element o)
    {
        return (type_ == o.type_ && priority_ == o.priority_ && str_ == o.str_);
    }
    bool operator<=(const Element o)
    {
        return (priority_ <= o.priority_);
    }

public:
    std::string str_;
private:
    ElementType type_;
    int priority_;
};

// 优先级表
// 01234567890123456789012345678901234567890123456789012345678901234567890
// +---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+
// |         | con var | #       | +-      | */      | fun     | ^       | (       | ,       | )       |
// +---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+
// | isp     | -1      | 0       | 3       | 4       | 5       | 6       | 1       |         |         |
// +---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+
// | osp     |         | 0       | 3       | 4       | 5       | 6       | 7       | 2       | 2       |
// +---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+
std::string END_NAME("###");
Element NullEle("#");
Element Left_B("(", 7);
Element Seprate(",", 2);
Element Right_B(")", 2);
Element Left_B_I("(", 1);

typedef std::map<std::string, Element> KeyElementMap;
const KeyElementMap::value_type  systemKeyPair[] =
{
    KeyElementMap::value_type("#", Element("#", ET_OPERATOR, 0)),
    KeyElementMap::value_type("+", Element("+", ET_OPERATOR, 3)),
    KeyElementMap::value_type("-", Element("-", ET_OPERATOR, 3)),
    KeyElementMap::value_type("*", Element("*", ET_OPERATOR, 4)),
    KeyElementMap::value_type("/", Element("/", ET_OPERATOR, 4)),
    KeyElementMap::value_type("^", Element("^", ET_OPERATOR, 6)),
    KeyElementMap::value_type("(", Element("(", ET_OPERATOR, 7)),
    KeyElementMap::value_type(",", Element(",", ET_OPERATOR, 2)),
    KeyElementMap::value_type(")", Element(")", ET_OPERATOR, 2)),
    KeyElementMap::value_type("sin", Element("sin", ET_OPERATOR, 5)),
    KeyElementMap::value_type("cos", Element("cos", ET_OPERATOR, 5)),
    KeyElementMap::value_type("tan", Element("tan", ET_OPERATOR, 5)),
    KeyElementMap::value_type("exp", Element("exp", ET_OPERATOR, 5))
};

const KeyElementMap systemKeyEleMap(systemKeyPair, systemKeyPair + 13); 

class RPN {
public:
    RPN(char *str) : originStr_(str), index_(0)
    {}
    RPN(const std::string & str) : originStr_(str), index_(0)
    {}
    bool getNextElement(Element & ele);
    void change();
    void print();
private:
    void skipBlank();
    void getName(std::string & name);
    bool isSysKey(std::string & name) {
        return systemKeyEleMap.find(name) != systemKeyEleMap.end();
    }
    bool isUserVar(std::string &name) {
        return userKeyEleMap_.find(name) != userKeyEleMap_.end();
    }
    bool isNumber(std::string &name) {
        return (name[0] >= '0' && name [0] <= '9');
    }

    bool isSimpleOP(char c) {
        return (c == '+' || c == '-' || c == '*' || 
                c == '/' || c == '^' || c == '(' || 
                c == ',' || c == ')');
    }

private:
    size_t index_;
    std::string originStr_;
    std::vector<Element> opStack_;
    std::vector<Element> rpn_;
    KeyElementMap userKeyEleMap_;
};

void RPN::skipBlank() {
    while (index_ < originStr_.size() && 
            (originStr_[index_] == ' ' || originStr_[index_] == '\t' || originStr_[index_] == '\n')) {
        index_++;
    }
}

void RPN::getName(std::string & name) {
    skipBlank();
    if (index_ >= originStr_.size()) {
        name = END_NAME;
        return ;
    }

    size_t i = index_;
    char c = originStr_[index_];
    if (c >= '0' && c <= '9') {
        while ( i < originStr_.size() && 
                ((originStr_[i]>= '0' && originStr_[i] <= '9') || originStr_[i] == '.')) {
            i++;
        }
        name = originStr_.substr(index_, i - index_);
        index_ = i;
    } else if (isSimpleOP(c)) {
        name = c;
        index_++;
    } else {
        while ( i < originStr_.size() && 
                ((originStr_[i]>= 'a' && originStr_[i] <= 'z') || 
                 (originStr_[i]>= '0' && originStr_[i] <= '9') ||
                 (originStr_[i]>= 'A' && originStr_[i] <= 'Z') || originStr_[i] == '_')) {
            i++;
        }
        if (i == index_) {
            name = originStr_.substr(index_, 1); // error
        } else {
            name = originStr_.substr(index_, i - index_);
        }
        index_ = i;
    }
}
bool RPN::getNextElement(Element & ele) {
    std::string name; 
    getName(name);
    if (name == END_NAME) {
        return false;
    }
    if (isSysKey(name)) {
        ele = systemKeyEleMap.find(name)->second;
        return true;
    }
    if (isUserVar(name)) {
        ele = userKeyEleMap_.find(name)->second;
        return true;
    }
    if (isNumber(name)) {
        ele = Element(name, ET_CONSTNUM, -1);
        return true;
    }

    std::cout << " Error: Unkonw " << name << std::endl;
    return false;
}

void RPN::change()
{
    Element ele;
    while (getNextElement(ele)) {
        if (ele.isOp()) {
            while ((!opStack_.empty()) && ele <= opStack_.back()) {
                rpn_.push_back(opStack_.back());
                opStack_.pop_back();
            }
            if (ele == Left_B)
            {
                opStack_.push_back(Left_B_I);
            }else if(ele == Right_B) {
                opStack_.pop_back();
            }else if (ele == Seprate) {
                // do nothing
            }else {
                opStack_.push_back(ele);
            }
        } else {
            rpn_.push_back(ele);
        }
        // print();
    }

    while (!opStack_.empty()) {
        rpn_.push_back(opStack_.back());
        opStack_.pop_back();
    }
    std::cout << "OriginStr: " << originStr_ << std::endl;
    print();
}

void RPN::print()
{
    std::cout << "OpStack:   ";
    for (int i = 0; i < opStack_.size(); ++i) {
        std::cout << opStack_[i].str_ << " " ;
    }
    std::cout << std::endl;
    std::cout << "---RPN:    ";
    for (int i = 0; i < rpn_.size(); ++i) {
        std::cout << rpn_[i].str_ << " ";
    }
    std::cout << std::endl;
}

//test
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
