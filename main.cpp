#include <iostream>
#include <signal.h>
#include "types.h"
#include "RK4.h"
#include "myException.h"

using namespace std;

mydouble test(mydouble x, mydouble y) {
    if(IS_ZERO(x)) {
        throw myException("Singular point", 0);
    }
    return 2 * x * x / x;
}

mydouble run(mydouble x, mydouble y) {
    if(IS_ZERO(x)) {
        throw myException("Singular point", 0);
    }
    return (2 * sqr(y) + 3 * x * y - 2 * x) / (2 * x * x);
}

void sigHup(int param) {
    cout << "sighup" << endl;
}

int main1() {
    signal(SIGHUP, sigHup);
    mydouble h = 0.1;
    RK4 rk4(run);
    mydouble x1, x2;
    cout << "#Input [x1, x2]" << endl;
    cin >> x1 >> x2;
    rk4.setSegment(x1, x2);
    mydouble x0, y0;
    cout << "#Input (x0, y0)" << endl;
    cin >> x0 >> y0;
    rk4.setStartValue(x0, y0);
    cout << "#Input start h" << endl;
    cin >> h;
    cout << "#Input N:" << endl;
    size_t N;
    cin >> N;
    rk4.addSingularity(0, 0);
    cout << "eps <= " << rk4.checkEps(h, eps, N) << endl;
    rk4.getListPoints().dump();
    cout << "h=" << h << endl;
    cout << run(1.99, 0.00667062) << endl;
    return 0;
}

int main() {
    try {
        main1();
    } catch (myException &ex) {
        cerr << ex.what();
    }
}