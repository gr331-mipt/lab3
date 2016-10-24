//
// Created by altair on 07.11.15.
//

#include <cmath>
#include <assert.h>
#include "RK4.h"
#include "myException.h"

mydouble RK4::calcNextY(const mydouble Xn, const mydouble Yn, const mydouble h) const {
        mydouble f1 = getFunc(Xn, Yn);
        mydouble f2 = getFunc(Xn + h / 2, Yn + h / 2 * f1);
        mydouble f3 = getFunc(Xn + h / 2, Yn + h / 2 * f2);
        mydouble f4 = getFunc(Xn + h, Yn + h * f3);
        return Yn + h / 6 * (f1 + 2 * f2 + 2 * f3 + f4);
}

void RK4::setStartValue(mydouble x0_, mydouble y0_) {
    x0 = x0_;
    y0 = y0_;
}

void RK4::setSegment(mydouble x1_, mydouble x2_) {
    x1 = x1_;
    x2 = x2_;
}

ListPoints RK4::integrate(const mydouble h_) const{
    ListPoints ret;
    mydouble i1 = x0;
    mydouble y1 = y0;
    mydouble y = y0;
    for (mydouble i = x0 + h_; i < x2; i1 = i, y1 = y, i += h_) {
        y = calcNextY(i1, y1, h_);
        ret.push_back(Point(i, y));
    }
    return ret;
}

mydouble RK4::checkEps(mydouble &h, mydouble eps, const size_t otrCount) {
    if(h < 0) {
        h = -h;
    }
    if(h > (x2 - x1) / 2 / otrCount) {
        h = (x2 - x1) / 2 / otrCount;
    }
    assert(h > 1e-7);
    cout << "#Start solving" << endl;
    mydouble ro = 0;
    mydouble x_n_1 = x0;
    mydouble y_n_1 = y0;
    mydouble x_n_2 = x0;
    mydouble y_n_2 = y0;
    size_t count = 1;
    size_t N = size_t((x2 - x1) / h / otrCount);
    if(N % 2 == 1) {
        N--;
    }
    if(N == 0) {
        N = 2;
    }
    do {
        count = 1;
        ro = 0;
        cout << "|";
        listPoints.clear();
        listPoints.push_back(Point(x0, y0, y0, 0));
        x_n_1 = x0;
        y_n_1 = y0;
        x_n_2 = x0;
        y_n_2 = y0;
        for (mydouble x_n = x0 + h; x_n < x2; x_n_2 = x_n_1, x_n_1 = x_n, x_n += h, count++) {
            y_n_1 = calcNextY(x_n_1, y_n_1, h);
            if (!(count % 2)) {
                y_n_2 = calcNextY(x_n_2, y_n_2, 2 * h);
                if (!(count % N)) {
                    ro += sqr(y_n_2 - y_n_1);
                    if(ro > eps)
                        break;
                    count = 0;
                    listPoints.push_back(Point(x_n, y_n_1, y_n_2, y_n_2 - y_n_1));
                    //cout << "(" << x_n << ", " << y_n_2 << ", " << y_n << ", " << y_n_2 - y_n << ")" << endl;
                }
            }
        }
        if (!(count % N)) {
            listPoints.push_back(Point(x2, y_n_1, y_n_2, y_n_2 - y_n_1));
            //cout << "(" << x_n << ", " << y_n_2 << ", " << y_n << ", " << y_n_2 - y_n << ")" << endl;
        }
        x_n_1 = x0;
        y_n_1 = y0;
        x_n_2 = x0;
        y_n_2 = y0;
        h = -h;
        count = 1;
        for (mydouble x_n = x0 + h; x_n > x1; x_n_2 = x_n_1, x_n_1 = x_n, x_n += h, ++count) {
            y_n_1 = calcNextY(x_n_1, y_n_1, h);
            if (!(count % 2)) {
                y_n_2 = calcNextY(x_n_2, y_n_2, 2 * h);
                if (!(count % N)) {
                    count = 0;
                    ro += sqr(y_n_2 - y_n_1);
                    if(ro > eps) {
                        break;
                    }
                    listPoints.push_front(Point(x_n, y_n_1, y_n_2, y_n_2 - y_n_1));
                    //cout << "(" << x_n << ", " << y_n_2 << ", " << y_n << ", " << y_n_2 - y_n << ")" << endl;
                }
            }
        }
        if (!(count % N)) {
            listPoints.push_back(Point(x2, y_n_1, y_n_2, y_n_2 - y_n_1));
            //cout << "(" << x_n << ", " << y_n_2 << ", " << y_n << ", " << y_n_2 - y_n << ")" << endl;
        }
        ro = std::sqrt(ro) / ((1 << 4) - 1);
        h /= -2;
        N *= 2;
    } while (ro > eps && h > 1e-7);
    h *= 2;
    cout << "y_n_1=" << y_n_1 << " y_n_2=" << y_n_2 << endl;
    cout << "\n#End solving" << endl;
    return ro;
}

void RK4::addSingularity(mydouble x, mydouble y) {
    singularities.push_back(Point(x, y));
}

mydouble RK4::getSingularity(mydouble x) const {
    for(ListPoints::const_iterator i = singularities.begin(); i != singularities.end(); i++) {
        if(IS_ZERO(x - i->x)) {
            return i->yh;
        }
    }
    throw myException("Unfind singular point");
}

mydouble RK4::getFunc(const mydouble x, const mydouble y) const {
    try {
        return func(x, y);
    }
    catch (myException &ex) {
        return getSingularity(ex.getX());
    }
}
