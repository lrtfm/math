/*
 * Mcommon.hpp
 *
 *  Created on: Nov 22, 2014
 *      Author: YangZongze
 */

#ifndef MCOMMON_HPP_
#define MCOMMON_HPP_

namespace MC {

const double epsilon = 0.00001;

#ifdef DEBUG
#include <iostream>
#define Debug(x) std::cerr << x;
#else
#define Debug(x)
#endif

}

#endif /* MCOMMON_HPP_ */
