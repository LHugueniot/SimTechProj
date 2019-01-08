#ifndef DISTCONSTRAINT_H
#define DISTCONSTRAINT_H

#include "clothsimlib.h"

namespace PBD {

class CLOTHSIMLIBSHARED_EXPORT distConstraint
{
public:
    distConstraint(PBDObj* pbdobj, int _pA, int _pB);
    ~distConstraint();
    
    float rLength;  //rest length for pa and pb
    float k;        
};
}
#endif // DISTCONSTRAINT_H
