#include "idealcomp.h"

IdealComp::IdealComp(CompType t)
{
    type = t;
}

std::complex<double> IdealComp::getZ(uint64_t freq) {
    switch(type) {
    case Res:
        return value;
    case Cap:
        return 1.0/(2.0*PI*(double)freq*value);
    case Ind:
        return 2.0*PI*(double)freq*value;
    }
}
