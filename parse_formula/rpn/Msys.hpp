/*
 * Msys.hpp
 *
 * YangZongze yangzongze@gmail.com
 */


#ifndef MSYS_HPP__
#define MSYS_HPP__

#include "Mtoken.hpp"
#include "Melement.hpp"

namespace MC {
    extern Element Lba;
    extern Element Lba_i;
    extern Element Rba;
    extern Element Com;

    extern TokenRule numRule;
    extern TokenProcess tokenProcess;
    extern TokenProcess varProcess;

    extern ElementClass systemElementClass;
    extern NumberElementClass numberElementClass;
}

#endif
