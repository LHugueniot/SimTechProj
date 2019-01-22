#include "collisionobj.h"

namespace PBD {

//-----------------------------------Collision shape stuff-----------------------

//------sphere-------

Sphere::Sphere(double _radius, glm::vec3 _pos)
{
    m_pos=_pos;
    m_radius=_radius;
    vertices.clear();
    vertices.push_back(m_pos);
}

void Sphere::CreateShape()
{
}

bool Sphere::CheckCollision(Point& p)
{
    for(uint k=0; k<vertices.size(); k++)
    {
        auto sCenter=m_pos;
        auto m = p.m_ppos - sCenter;
        float b = glm::dot(m, p.tmp_pos);
        float c = glm::dot(m,m) - m_radius * m_radius;
        if(c > 0.0f && b >0.0f) continue;
        float discr= b*b -c;

        if(discr< 0.0f) continue;

        float t= -b - glm::sqrt(discr);

        if(t<0.0f) t=0.0f;
        p.tmp_pos= p.m_ppos + t * p.tmp_pos;
        p.m_pvel=glm::vec3(0,0,0);
    }
}

bool Sphere::CheckCollision1(int k, glm::vec3 _ray)
{
    if(m_radius>glm::distance(_ray,m_pos))
    {
        return true;
    }
    else
    {
        return false;
    }
}
//-------plain------

Plain::Plain(int _width, int _height, glm::vec3 _pos)
{
    m_width=_width;
    m_height=_height;
    m_pos=_pos;
}

void Plain::CreateShape()
{
    vertices.push_back(m_pos);
    vertices.push_back(m_pos+glm::vec3(m_width,0,0));
    vertices.push_back(m_pos+glm::vec3(0,0,m_height));
    vertices.push_back(m_pos+glm::vec3(m_width,0,m_height));
}

bool Plain::CheckCollision(Point& p)
{
}

}
