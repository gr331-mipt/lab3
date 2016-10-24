//
// Created by altair on 07.11.15.
//

#ifndef LABA3_TYPES_H
#define LABA3_TYPES_H

typedef long double mydouble;
const mydouble eps = 1e-4;
const mydouble eps2 = 1e-8;

inline bool IS_ZERO(mydouble x) {
    return (-eps2 < x && x < eps2);
}

inline mydouble sqr(mydouble x) {
    return x * x;
}

#endif //LABA3_TYPES_H
