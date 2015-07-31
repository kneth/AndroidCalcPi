#include <cstddef>
#include <stdexcept>

#include <sys/time.h>

#include "rng.hpp"
#include "pi.hpp"

using namespace std;

Pi::Pi(size_t iterations) {
    if (iterations < 1) {
        throw runtime_error("number of iterations must be larger than 0");
    }
    m_iterations = iterations;

    // get a new seed every time
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    m_rng = new RNG(ms);
}

double Pi::estimate() {
    size_t n_hits = 0;
    for (size_t i = 0; i < m_iterations; ++i) {
        double x = m_rng->uniform();
        double y = m_rng->uniform();
        if (x*x + y*y < 1.0) {
            n_hits++;
        }
    }
    return 4.0*static_cast<double>(n_hits)/static_cast<double>(m_iterations);
}
