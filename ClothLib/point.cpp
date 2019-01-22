#include "point.h"

namespace PBD {

Point::Point(glm::vec3 _pos,glm::vec3 _pvel , float _pmass)
{
    m_ppos=_pos;
    m_pvel=_pvel;
    m_pmass=_pmass;
    m_invMass=1/m_pmass;
    tmp_pos=glm::vec3(0,0,0);
}

Point::~Point()
{
}

void Point::update()
{
    m_pvel=+m_pvel*m_pmass;
}

}
