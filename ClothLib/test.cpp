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
    m_restLength=(m_pA->m_ppos - m_pA->m_ppos).length();
}

void DistanceConstraint::update()
{

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

}

void PBDobj::addConstraint(DistanceConstraint* m_Constraint)
{
    m_ConPtrs.push_back(m_Constraint);
}

void PBDobj::addObjectToList(CollisionObj * _newColObj)
{
    OtherObjs.push_back(_newColObj);
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
        std::cout<<"PA ("<<pA.x<<" "<<pA.y<<" "<<pA.z<<") ";
        std::cout<<"PB ("<<pB.x<<" "<<pB.y<<" "<<pB.z<<") \n";
    }
}

void PBDobj::runSolver(float dt)
{
    //Predict Location
    float inv_dt=1/dt;
    for (uint i=0; i<m_PointsPtr.size(); i++)
    {
        Point& p = *(m_PointsPtr[i]);
        p.m_pvel+=m_grav*inv_dt;
        p.tmp_pos=p.m_ppos+p.m_pvel*inv_dt;

        for(uint j=0; j<OtherObjs.size(); j++)
        {
            CollisionObj& o= *(OtherObjs[j]);
            auto a=glm::normalize(p.tmp_pos);
            a*=0.05;
            while (!aproximateVec3(p.tmp_pos,a,0.1))
            {
                if(aproximateVec3(a,p.tmp_pos,o._radius));
                {
                    p.tmp_pos=p.m_ppos;

                }
                a=a+a;
            }
        }

    }

    for (uint i=0; i<m_ConPtrs.size(); i++)
    {

    }
    //update constraints

    //update position
    for (uint i=0; i<m_PointsPtr.size(); i++)
    {
        Point& p = *(m_PointsPtr[i]);
        p.m_ppos+=p.m_pvel;
    }
}

//-----------------------------------Collision shape stuff-----------------------

//------sphere-------

Sphere::Sphere(float _radius)
{

}

void Sphere::CreateShape()
{

}

bool Sphere::CheckCollision(glm::vec3)
{

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

bool Plain::CheckCollision(glm::vec3)
{

}
