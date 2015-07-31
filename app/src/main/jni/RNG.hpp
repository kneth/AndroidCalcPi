#ifndef __RNG_HPP__
#define __RNG_HPP__

class RNG {
public:
    RNG(long seed);
    double uniform();
    void gauss2d(double &, double &);
private:
    long m_w;
    long m_z;
};

#endif // __RNG_HPP__
