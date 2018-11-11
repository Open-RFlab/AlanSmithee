#ifndef COMPONENT_H
#define COMPONENT_H

#include <complex>

const double PI = 3.141592653589793238463;

class Component
{
public:
    Component();
    virtual std::complex<double> getZ(uint64_t freq);

};

#endif // COMPONENT_H
