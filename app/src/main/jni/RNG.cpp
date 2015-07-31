#include "RNG.hpp"

#include <cstdlib>
#include <cmath>

RNG::RNG(long seed) {
    srand48(static_cast<unsigned>(seed));
}

double RNG::uniform() {
    return static_cast<double>(lrand48()) / static_cast<double>(RAND_MAX);
}

void RNG::gauss2d(double &x, double &y) {
    double r;
    do {
        x = 2.0*uniform() - 1.0;
        y = 2.0*uniform() - 1.0;
        r = x*x + y*y;
    } while ((r > 1.0) || (r == 0.0));
    double factor = sqrt(-2.0*log(r)/r);
    x *= factor;
    y *= factor;
}

