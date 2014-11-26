#include <iostream>
#include <vector>
#include <stack>

enum ElementType {
    ET_OPERATOR;   // +-*/^
    ET_FUNCTION;   // sin cos exp
    ET_VARIATION;  // x y z   TODO
    ET_CONSTNUM;   // 1 2 3 
};

class Element {
public:
    Element(char *str):str_(str), type_(ET_OPERATOR), priority_(0) {}
    Element(char c, int priority):str_(str), type_(ET_OPERATOR), priority_(priority) {}
    Element(char *str, int priority):str_(str), type_(ET_OPERATOR), priority_(priority) {}
    Element(char *str, ElementType type, int priority):str_(str), type_(type), priority_(priority) {}

    bool isOp() { return type_ == ET_OPERATOR;}
    bool isFun() { return type_ == ET_FUNCTION;}
    bool operator==(const Element o)
    {
        return (type_ == o.type_ && priority_ == o.priority_ && str_ == o.str_);
    }
    bool operator<=(const Element o)
    {
        return (priority_ <= o.priority_);
    }

private:
    ElementType type_;
    int priority_;
    std::string str_;
};

// 优先级表
// 01234567890123456789012345678901234567890123456789012345678901234567890
// +---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+
// |         | con var | #       | +-      | */      | fun     | ^       | (       | ,       | )       |
// +---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+
// | isp     | -1      | 0       | 3       | 4       | 5       | 6       | 1       |         |         |
// +---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+
// | osp     |         | 0       | 3       | 4       | 5       | 6       | 7       | 2       | 1       |
// +---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+
Element NullEle("#");
Element Left_B("(", 7);
Element Left_B_I("(", 1);
Element Seprate(",", 2);
Element Right_B(")", 1);

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
    size_t index_;
    std::string originStr_;
    std::stack<Element> opStack_;
    std::vector<Element> rpn_;
};

bool RPN::getNextElement(Element & ele) {
    skipBlank();
    char c = originStr_[index_];
    if (c >= '0' && c <= '9') {

    }
    else if (isSimpleOP(c)) {
        switch (c) {
            case '+':
            case '-':
                index_++;
                ele = Element(c, 3);
                break;
            case '*':
            case '/':
                index_++;
                ele = Element(c, 4);
                break;
            case '^':
                index_++;
                ele = Element(c, 6);
                break;
            case '(':
                index_++;
                ele = Left_B;
                break;
            case ')':
                index_++;
                ele = Right_B;
                break;
            default:
                break;
        }
    } else {

    }

    return true;     
}

void RPN::change()
{
    Element e;
    while (getNextElement(ele)) {
        if (ele.isOp()) {
            while ((!opStack_.empty()) && ele <= opStack_.top()) {
                rpn_.push_back(opStack_.pop());
            }
            if (ele == Left_B)
            {
                opStack_.push(Left_B_I);
            }else if(ele == Right_B || ele == Seprate) {
                // do nothing
            }else {
                opStack_.push(ele);
            }
        } else {
            rpn_.push_back(ele);
        }
    }

    while (opStack_.empty()) {
        rpn_.push_back(opStack_.pop());
    }
}

void RPN::print()
{
    for (int i = 0; i < rpn_.size(); ++i) {
        std::cout << rpn_[i] << " ";
    }
    std::cout << std::endl;
}
