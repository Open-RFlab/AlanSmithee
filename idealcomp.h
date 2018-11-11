#ifndef IDEALCOMP_H
#define IDEALCOMP_H

#include "component.h"

enum CompType {
    Res,
    Cap,
    Ind
};

class IdealComp : public Component
{
public:
    IdealComp(CompType t);

    std::complex<double> getZ(uint64_t freq);

    CompType type;
    double value;

};

#endif // IDEALCOMP_H
