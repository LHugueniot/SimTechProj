#include "constraints.h"

namespace PBD {

DistanceConstraint::DistanceConstraint(Point *_pA, Point *_pB)
{
    m_pA=_pA;
    m_pB=_pB;
    m_restLength=glm::length(m_pA->m_ppos - m_pB->m_ppos);
}

DistanceConstraint::~DistanceConstraint(){}

void DistanceConstraint::update()
{
    glm::vec3 dir = m_pA->tmp_pos - m_pB->tmp_pos;
    float len = glm::length(dir);
    float inv_mass=m_pA->m_invMass + m_pB->m_invMass;

    //std::cout<<len<<"\n";

    m_pA->tmp_pos-=((m_pA->m_invMass/inv_mass)*
                     (len - m_restLength)*
                     (dir/len));

    m_pB->tmp_pos+=((m_pB->m_invMass/inv_mass)*
                    (len -m_restLength)*
                    (dir/len));
}

BendingConstraint::BendingConstraint(Point *_pA, Point *_pB, Point *_pC)
{

}

void BendingConstraint::update()
{

}

}
