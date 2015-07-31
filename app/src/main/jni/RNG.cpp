#include "RNG.hpp"

#include <cstdlib>
#include <cmath>
#include <climits>

RNG::RNG(long seed) {
    if (seed == 0) {
        seed = 1;
    }
    m_w = seed;
    m_z = seed;
}

double RNG::uniform() {
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    uint n = (m_z << 16) + m_w;
    return static_cast<double>(n) / static_cast<double>(UINT_MAX);
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

