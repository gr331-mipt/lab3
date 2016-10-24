//
// Created by altair on 16.11.15.
//

#include "myException.h"

const char *myException::what() const throw() {
    return str;
}
