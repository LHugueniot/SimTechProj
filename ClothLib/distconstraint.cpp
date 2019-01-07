#include "distconstraint.h"

namespace PBD {

distConstraint::distConstraint(PBDObj* pbdobj, int _pA, int _pB)
{
    auto m_pA=pbdobj->m_ppos[_pA];
    auto m_pB=pbdobj->m_ppos[_pB];
    rLength=glm::distance(m_pA,m_pB);
}

distConstraint::~distConstraint()
{

}

}
