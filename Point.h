//
// Created by altair on 07.11.15.
//

#ifndef LABA3_POINT_H
#define LABA3_POINT_H


#include "types.h"
#include <list>
#include <iostream>

using std::list;
using std::cout;
using std::endl;

class Point {
public:
    mydouble x;
    mydouble yh;
    mydouble y2h;
    mydouble delta;

    Point(const mydouble x, const mydouble y, const mydouble y2 = 0, const mydouble delta = 0) : x(x), yh(y), y2h(y2), delta(delta) {}
};

class ListPoints: public list< Point > {
public:
    void dump() {
        cout << "#LIST DUMP" << endl << "#SIZE:" << size() << endl;
        for(ListPoints::iterator i = this->begin(); i != this->end(); i++) {
            cout <<"(" << i->x << ", " << i->yh << ", " << i->y2h << ", " << i->delta <<")" << endl;
        }
        cout << "#END DUMP" << endl;
    }
};


#endif //LABA3_POINT_H
