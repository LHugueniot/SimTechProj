#include "clothsimlib.h"

namespace PBD {



ClothSim::ClothSim()
{

}


ClothSim::~ClothSim()
{

}

void ClothSim::makeMesh(glm::vec3 _pos,int _width, int _height, float _patchsize)
{
    auto m_pos=_pos;
    m_initpatchsize = _patchsize;
    m_width=_width;
    m_height=_height;
    for(int i=0; i<m_width; i++)
    {
        for(int j=0;j<m_height; j++)
        {
            //auto f=m_pos + glm::vec3(i*0.5,j*0.5,0);
            makeSmolMesh(m_pos + glm::vec3(i*0.5,j*-0.5,0),0.5);
            //std::cout<<j<<" "<<i<<" "<<f.x<<" "<<f.y<<" "<<f.z<<" \n";
        }
    }
}

void ClothSim::makeSmolMesh(glm::vec3 _pos, float _patchsize)
{
    auto m_patchsize=_patchsize;
    auto m_pos=_pos;
    auto tri1=makeTriangle(m_pos, m_patchsize);
    m_ppos.push_back(tri1.a);
    m_ppos.push_back(tri1.b);
    m_ppos.push_back(tri1.c);
    auto tri2=triMirror(tri1, m_patchsize);
    m_ppos.push_back(tri2.a);
    m_ppos.push_back(tri2.b);
    m_ppos.push_back(tri2.c);

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
