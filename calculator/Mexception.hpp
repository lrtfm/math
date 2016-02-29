/*
 * Mexception.hpp
 *
 * YangZongze yangzongze@gmail.com
 */

#ifndef MEXCEPTION_HPP__
#define MEXCEPTION_HPP__

#include <string>

class ExceptionBase {
public:
    ExceptionBase()
    {}
    ExceptionBase(const char * info)
        : info_(info)
    {}
    ExceptionBase(const std::string & info)
        : info_(info)
    {}

    virtual ~ExceptionBase()
    {}

    std::string & info()
    {
        return info_;
    }

private:
    std::string info_;
};

#endif
