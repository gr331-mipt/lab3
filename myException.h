//
// Created by altair on 16.11.15.
//

#ifndef LABA3_MYEXCEPTION_H
#define LABA3_MYEXCEPTION_H


#include <exception>
#include <string>
#include "types.h"

class myException: protected std::exception {
    const char *str;
    const mydouble x;
public:
    myException(const char *str, const mydouble x = 0): str(str), x(x){ }

    virtual const char *what() const throw() ;

    const mydouble getX() const {
        return x;
    }
};


#endif //LABA3_MYEXCEPTION_H
