#include "clothsimlib.h"

namespace PBD {



PBDObj::PBDObj()
{

}


PBDObj::~PBDObj()
{

}


float PBDObj::PointMass(int _vecindex) const
{
    int m_vecindex=_vecindex;
    return m_pmass[m_vecindex];
}

glm::vec3 PBDObj::PointPos(int _vecindex) const
{
    int m_vecindex=_vecindex;
    return m_ppos[m_vecindex];
}

glm::vec3 PBDObj::PointVel(int _vecindex) const
{
    int m_vecindex=_vecindex;
    return m_pvel[m_vecindex];
}

void PBDObj::setPointMass(int _vecindex, float _mass)
{
    int m_vecindex=_vecindex;
    float m_mass=_mass;
    m_pmass[m_vecindex]=m_mass;
}

void PBDObj::setPointPos(int _vecindex, glm::vec3 _pos)
{
    int m_vecindex=_vecindex;
    glm::vec3 m_pos=_pos;
    m_ppos[m_vecindex]=m_pos;

}
void PBDObj::setPointVel(int _vecindex, glm::vec3 _vel)
{
    int m_vecindex=_vecindex;
    glm::vec3 m_vel=_vel;
    m_ppos[m_vecindex]=m_vel;
}

Tri makeTriangle(glm::vec3 _pos, float _patchsize )
{
    auto m_initpatchsize = _patchsize;
    auto m_pos=_pos;
    Tri triangle;
    triangle.a=m_pos;
    triangle.b=m_pos + glm::vec3(m_initpatchsize,0,0);
    triangle.c=m_pos + glm::vec3(0,m_initpatchsize,0);
    return triangle;
}

Tri triMirror(Tri _patch,float _patchsize )
{
    auto m_initpatchsize = _patchsize;
    Tri triangle;
    triangle.a=_patch.b;
    triangle.b=_patch.a+glm::vec3(m_initpatchsize,m_initpatchsize,0);
    triangle.c=_patch.c;
    return triangle;
}


}
