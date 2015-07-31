#ifndef __PI_HPP__
#define __PI_HPP__

#include <cstddef>
#include <vector>

#include "RNG.hpp"

class Pi {
public:
    Pi(std::size_t, std::size_t);
    double estimate(std::size_t);
private:
    size_t m_iterations;
    std::vector<RNG *> m_rng;
};

#endif // __PI_HPP__
