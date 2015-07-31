#ifndef __RNG_HPP__
#define __RNG_HPP__

class RNG {
public:
    RNG(long seed);
    double uniform();
    void gauss2d(double &, double &);
private:
};

#endif // __RNG_HPP__
