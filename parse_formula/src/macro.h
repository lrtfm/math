/*
 *
 *
 *
 *
 */

#ifndef MACRO_H__
#define MACRO_H__

#define CHECK_PARA(n, i, para) \
{\
    if (n != i && para == NULL) {\
        /* TODO error process. */\
        return 0.0; \
    }\
}

#endif
