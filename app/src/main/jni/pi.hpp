#ifndef __PI_HPP__
#define __PI_HPP__

#include <cstddef>

#include "RNG.hpp"

class Pi {
public:
    Pi(std::size_t);
    double estimate();
private:
    size_t m_iterations;
    RNG *m_rng;
};

#endif // __PI_HPP__
