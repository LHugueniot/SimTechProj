#include "test.h"

bool aproximateVec3(glm::vec3 a, glm::vec3 b, float dif)
{
    if(a.x+dif>(b.x) && a.x-dif<(b.x))
    {
        if(a.y+dif>(b.y) && a.y-dif<(b.y))
        {
            if(a.z+dif>(b.z) && a.z-dif<(b.z))
            {
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

//------------------------------------------triangle stuff----------------------------

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


//-------------------------------------------points functions-------------------------
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

//----------------------------------------Constraint functions------------------------------

DistanceConstraint::DistanceConstraint(Point *_pA, Point *_pB)
{
    m_pA=_pA;
    m_pB=_pB;
    m_restLength=glm::length(m_pA->m_ppos - m_pB->m_ppos);
    //std::cout<<"m_restLength"<<m_restLength;
}

DistanceConstraint::~DistanceConstraint(){}

void DistanceConstraint::update()
{
    glm::vec3 dir = m_pA->m_ppos - m_pB->m_ppos;
    float len = glm::fastLength(dir);
    std::cout<<"len"<<len;
    float inv_mass=m_pA->m_invMass + m_pA->m_invMass;
    float diff = ((m_restLength - len) / (inv_mass*len));

    dir*= diff;
    //dir*= (f/len);
    if(m_pA->m_invMass!=0) {

        m_pA->tmp_pos +=dir;// (dir * m_pA->m_invMass);
        //std::cout<<"m_pA"<<m_pA->tmp_pos.x<<" "<<m_pA->tmp_pos.y<<" "<<m_pA->tmp_pos.z<<"\n";
        //std::cout<<m_pA->m_ppos.x<<" "<<m_pA->m_ppos.y<<" "<<m_pA->m_ppos.z<<"\n";
    }
    if(m_pB->m_invMass!=0) {
        m_pB->tmp_pos -=dir;// (dir * m_pB->m_invMass);
        //std::cout<<"m_pB"<<m_pB->tmp_pos.x<<" "<<m_pB->tmp_pos.y<<" "<<m_pB->tmp_pos.z<<"\n";
        //std::cout<<m_pB->m_ppos.x<<" "<<m_pB->m_ppos.y<<" "<<m_pB->m_ppos.z<<"\n";
    }
}

BendingConstraint::BendingConstraint(Point *_pA, Point *_pB, Point *_pC)
{

}

void BendingConstraint::update()
{

}

//---------------------------------------One class to rule them all-------------------------

PBDobj::PBDobj()
{

}

PBDobj::~PBDobj()
{
    for(uint p=0; p<m_ConPtrs.size(); p++)
    {
        delete m_ConPtrs[p];
    }
    for(uint i=0 ;i< m_PointsPtr.size(); i++)
    {
        delete m_PointsPtr[i];
    }
}

void PBDobj::addConstraint(DistanceConstraint* m_Constraint)
{
    m_ConPtrs.push_back(m_Constraint);
}

void PBDobj::addObjectToList(CollisionObj * _newColObj)
{
    OtherObjs.push_back(_newColObj);
    std::cout<<_newColObj;
}

void PBDobj::initialize(glm::vec3 _pos, int _width, int _height, float _patchsize, float _damping)
{
    m_patchsize = _patchsize;
    m_width=_width;
    m_height=_height;
    m_pos=_pos;
    m_damp=_damping;

    //--------------------------------

    for(uint i=0; i<m_width; i++)
    {
        for(uint j=0;j<m_height; j++)
        {
            //            auto tri1=makeTriangle(m_pos, m_patchsize);
            //            m_PointsPtr->m_ppos.push_back(tri1.a);
            //            m_PointsPtr->m_ppos.push_back(tri1.b);
            //            m_PointsPtr->m_ppos.push_back(tri1.c);
            //            auto tri2=triMirror(tri1, m_patchsize);
            //            m_PointsPtr->m_ppos.push_back(tri2.a);
            //            m_PointsPtr->m_ppos.push_back(tri2.b);
            //            m_PointsPtr->m_ppos.push_back(tri2.c);
            Point * newp = new Point(m_pos +glm::vec3( i*m_patchsize,j*-m_patchsize,0),glm::vec3(0,0,0), 1);
            m_PointsPtr.push_back(newp);
        }
    }

    for(uint i=0 ;i< m_PointsPtr.size(); i++)
    {
        for(uint j=0 ;j< m_PointsPtr.size(); j++)
        {
            auto a0 = m_PointsPtr.at(i)->m_ppos;
            auto b0 = m_PointsPtr.at(j)->m_ppos;
            auto a1 = a0+ glm::vec3(m_patchsize, 0, 0);
            auto a2 = a0+ glm::vec3(0, m_patchsize, 0);
            auto a3 = a0+ glm::vec3(m_patchsize, m_patchsize, 0);
            if(aproximateVec3(b0,a1,0.05)==true ||
                    aproximateVec3(b0,a2,0.05) ||
                    aproximateVec3(b0,a3,0.05))
            {
                DistanceConstraint* _Con= new DistanceConstraint(m_PointsPtr[i], m_PointsPtr[j]);
                addConstraint(_Con);
            }

        }
    }
    for(uint p=0; p<m_ConPtrs.size(); p++)
    {
        auto pA = m_ConPtrs[p]->m_pA->m_ppos;
        auto pB = m_ConPtrs[p]->m_pB->m_ppos;
        //std::cout<<"PA ("<<pA.x<<" "<<pA.y<<" "<<pA.z<<") ";
        //std::cout<<"PB ("<<pB.x<<" "<<pB.y<<" "<<pB.z<<") \n";
    }
}


void PBDobj::runSolver(float dt)
{
    //Predict Location

    float inv_dt=1/dt;
    for (uint i=0; i<m_PointsPtr.size(); i++)
    {
        Point& p = *(m_PointsPtr[i]);
        p.m_pvel+=m_grav*m_damp*inv_dt*p.m_invMass;
        p.tmp_pos=p.m_ppos+p.m_pvel*inv_dt;

        if(OtherObjs.size()>0)
        {
            for(uint j=0; j<OtherObjs.size(); j++)
            {

                CollisionObj& o = *(OtherObjs[j]);
                //std::cout<<o.vertices.size();
                for(uint k=0;k<o.vertices.size(); k++)
                {
                    if(o.CheckCollision(k,p.tmp_pos)==true)
                    {
                        //                    p.tmp_pos=p.m_ppos;
                        //a+=0.05;
                        p.tmp_pos=p.m_ppos;
                    }
                }
            }
        }
    }

    //update constraints
    for (uint i=0; i<m_ConPtrs.size(); i++)
    {
//        for(uint j=0; j<2; j++)
//        {
//            m_ConPtrs[i]->update();
//        }
        m_ConPtrs[i]->update();
    }

    //update position
    for (uint i=0; i<m_PointsPtr.size(); i++)
    {
        Point& p = *(m_PointsPtr[i]);
        p.m_ppos=p.tmp_pos;
        //std::cout<<p.tmp_pos.x<<" "<<p.tmp_pos.y<<" "<<p.tmp_pos.z<<"\n";
    }
    //std::cout<<p.m_ppos.x<<" "<<p.m_ppos.y<<" "<<p.m_ppos.z<<"\n";

}

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

bool Sphere::CheckCollision(uint _index, glm::vec3 _ray)
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

Plain::Plain(int _width, int _height, float _patchSize, glm::vec3 _pos)
{
    m_width=_width;
    m_height=_height;
    m_patchSize=_patchSize;
    m_pos=_pos;
}

void Plain::CreateShape()
{
    for(uint i=0 ;i<m_width; i++)
    {
        for(uint j=0; j< m_height; j++)
        {
            vertices.push_back(glm::vec3(i*m_patchSize,0,j*m_patchSize));
        }
    }
}

bool Plain::CheckCollision(uint _index,glm::vec3 _ray)
{
    if(aproximateVec3(vertices[_index],_ray, m_radius)==true)
    {
        return true;
    }
    else
    {
        return false;
    }

}
