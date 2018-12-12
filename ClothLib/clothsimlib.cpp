#include "clothsimlib.h"


ClothSim::ClothSim(int _width, int _length, float _patchsize)
{
    m_initpatchsize = _patchsize;
    m_width = _width;
    m_length = _length;
    m_pnum =m_length * m_width;
    for(int i=0; i<m_pnum; i++)
    {
        auto a =glm::vec3(0,0,0);
        m_ppos.push_back(a);
    }
}

ClothSim::~ClothSim()
{

}

float ClothSim::PointMass(int _vecindex) const
{
    int m_vecindex=_vecindex;
    return m_pmass[m_vecindex];
}
glm::vec3 ClothSim::PointPos(int _vecindex) const
{
    int m_vecindex=_vecindex;
    return m_ppos[m_vecindex];
}
glm::vec3 ClothSim::PointVel(int _vecindex) const
{
    int m_vecindex=_vecindex;
    return m_pvel[m_vecindex];
}

void ClothSim::setPointMass(int _vecindex, float _mass)
{
    int m_vecindex=_vecindex;
    float m_mass=_mass;
    m_pmass[m_vecindex]=m_mass;
}
void ClothSim::setPointPos(int _vecindex, glm::vec3 _pos)
{
    int m_vecindex=_vecindex;
    glm::vec3 m_pos=_pos;
    m_ppos[m_vecindex]=m_pos;

}
void ClothSim::setPointVel(int _vecindex, glm::vec3 _vel)
{
    int m_vecindex=_vecindex;
    glm::vec3 m_vel=_vel;
    m_ppos[m_vecindex]=m_vel;
}
