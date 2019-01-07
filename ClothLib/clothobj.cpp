#include "clothobj.h"

namespace PBD {

ClothObj::ClothObj()
{

}

ClothObj::~ClothObj()
{

}

void ClothObj::makeMesh(glm::vec3 _pos,int _width, int _height, float _patchsize)
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

void ClothObj::makeSmolMesh(glm::vec3 _pos, float _patchsize)
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

}
