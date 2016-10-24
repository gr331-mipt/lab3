//
// Created by altair on 07.11.15.
//

#ifndef LABA3_RK4_H
#define LABA3_RK4_H


#include "types.h"
#include "Point.h"

class RK4 {
protected:
    mydouble (*func)(mydouble x, mydouble y);
    mydouble x0;
    mydouble y0;
    mydouble x1;
    mydouble x2;

    ListPoints listPoints;
    ListPoints singularities;

public:
    RK4(mydouble (*f)(mydouble x, mydouble y)) {
        func = f;
    }

    mydouble calcNextY(const mydouble Xn, const mydouble Yn, const mydouble h) const ;

    void setStartValue(mydouble x0_, mydouble y0_);
    void setSegment(mydouble x1_, mydouble x2_);
    void addSingularity(mydouble x, mydouble y);
    mydouble getSingularity(mydouble x) const;
    mydouble getFunc(const mydouble x, const mydouble y) const;

    ListPoints integrate(const mydouble h_) const;

    mydouble checkEps(mydouble &h, mydouble eps, const size_t otrCount = 10);

    ListPoints &getListPoints() {
        return listPoints;
    }
};


#endif //LABA3_RK4_H
