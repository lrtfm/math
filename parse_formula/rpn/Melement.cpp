/*
 * Melement.hpp
 *
 * YangZongze yangzongze@gmail.com
 */

#include "Melement.hpp"

// 优先级表
// 01234567890123456789012345678901234567890123456789012345678901234567890
// +---------+---------+---------+---------+---------+---------+---------+
// |         | con var | #       | +-      | */      | fun     | ^       |
// +---------+---------+---------+---------+---------+---------+---------+
// | isp     | -1      | 0       | 3       | 4       | 5       | 6       |
// +---------+---------+---------+---------+---------+---------+---------+
// | osp     |         | 0       | 3       | 4       | 5       | 6       |
// +---------+---------+---------+---------+---------+---------+---------+
// +---------+---------+---------+---------+
// |         | (       | ,       | )       |
// +---------+---------+---------+---------+
// | isp     | 1       |         |         |
// +---------+---------+---------+---------+
// | osp     | 7       | 2       | 2       |
// +---------+---------+---------+---------+

std::string END_NAME("###");
Element Left_B("(", 7);
Element Seprate(",", 2);
Element Right_B(")", 2);
Element Left_B_I("(", 1);

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

