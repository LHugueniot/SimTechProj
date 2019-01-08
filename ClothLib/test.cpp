#include "test.h"

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
Points::Points()
{

}

float Points::PointMass(int _vecindex) const
{
    int m_vecindex=_vecindex;
    return m_pmass[m_vecindex];
}

glm::vec3 Points::PointPos(int _vecindex) const
{
    int m_vecindex=_vecindex;
    return m_ppos[m_vecindex];
}

glm::vec3 Points::PointVel(int _vecindex) const
{
    int m_vecindex=_vecindex;
    return m_pvel[m_vecindex];
}

void Points::setPointMass(int _vecindex, float _mass)
{
    int m_vecindex=_vecindex;
    float m_mass=_mass;
    m_pmass[m_vecindex]=m_mass;
}

void Points::setPointPos(int _vecindex, glm::vec3 _pos)
{
    int m_vecindex=_vecindex;
    glm::vec3 m_pos=_pos;
    m_ppos[m_vecindex]=m_pos;

}
void Points::setPointVel(int _vecindex, glm::vec3 _vel)
{
    int m_vecindex=_vecindex;
    glm::vec3 m_vel=_vel;
    m_ppos[m_vecindex]=m_vel;
}

//----------------------------------------Constraint functions------------------------------

Constraint::Constraint(Points* _points, int _pAindex, int _pBindex, float _pConRes)
{
    m_pA=_pAindex;
    m_pB=_pBindex;
    restLength=(_points->m_ppos[m_pA] - _points->m_ppos[m_pA]).length();
}

Constraint::~Constraint()
{

}

void Constraint::update()
{

}

//---------------------------------------One class to rule them all-------------------------

PBDobj::PBDobj(std::vector<Constraint*> _ConPtrs, Points* _PointsPtr)
{
    m_ConPtrs = _ConPtrs;
    m_PointsPtr = _PointsPtr;
}

PBDobj::~PBDobj()
{

}

void PBDobj::addConstraint(Constraint* m_Constraint)
{
    m_ConPtrs.push_back(m_Constraint);
}

void PBDobj::initialize(glm::vec3 _pos,int _width, int _height, float _patchsize)
{

    auto m_pos=_pos;
    auto m_patchsize = _patchsize;
    auto m_width=_width;
    auto m_height=_height;
    for(int i=0; i<m_width; i++)
    {
        for(int j=0;j<m_height; j++)
        {
//            auto tri1=makeTriangle(m_pos, m_patchsize);
//            m_PointsPtr->m_ppos.push_back(tri1.a);
//            m_PointsPtr->m_ppos.push_back(tri1.b);
//            m_PointsPtr->m_ppos.push_back(tri1.c);
//            auto tri2=triMirror(tri1, m_patchsize);
//            m_PointsPtr->m_ppos.push_back(tri2.a);
//            m_PointsPtr->m_ppos.push_back(tri2.b);
//            m_PointsPtr->m_ppos.push_back(tri2.c);
            m_PointsPtr->m_ppos.push_back(glm::vec3(i*m_patchsize, j*m_patchsize, 0);
            m_PointsPtr->m_pmass.push_back(1);
            m_PointsPtr->m_pvel.push_back(0);
        }
    }
    for(int i=0; i<m_PointsPtr->m_ppos.size(); i++)
    {
        if(i!=0 && i%6 ==0)
        {
            Constraint* _Con1= new Constraint(m_PointsPtr, i, i+1,1.0f);
            addConstraint(_Con1);
            Constraint* _Con2= new Constraint(m_PointsPtr, i+1, i+2,0.5f);
            addConstraint(_Con2);
            Constraint* _Con3= new Constraint(m_PointsPtr, i+2, i,1.0f);
            addConstraint(_Con3);
            Constraint* _Con4= new Constraint(m_PointsPtr, i+1, i+4,1.0f);
            addConstraint(_Con4);
            Constraint* _Con5= new Constraint(m_PointsPtr, i+4 ,i+2,1.0f);
            addConstraint(_Con5);
        }
    }
    /*
    glm::vec3 point[] = //{glm::vec3(0,0,0),glm::vec3(0,0,0)};
    {
    glm::vec3(0, 0, 0), glm::vec3(0.5, 0, 0.5), glm::vec3(0, 0.5, 0),
    glm::vec3(0.5, 0, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0, 0.5, 0),
    glm::vec3(0, -0.5, 0), glm::vec3(0.5, -0.5, 0.5), glm::vec3(0, 0, 0),
    glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.5, 0, 0.5), glm::vec3(0, 0, 0),
    glm::vec3(0, -1, 0), glm::vec3(0.5, -1, 0.5), glm::vec3(0, -0.5, 0),
    glm::vec3(0.5, -1, 0.5), glm::vec3(0.5, -0.5, 0.5), glm::vec3(0, -0.5, 0),
    glm::vec3(0, -1.5, 0), glm::vec3(0.5, -1.5, 0.5), glm::vec3(0, -1, 0),
    glm::vec3(0.5, -1.5, 0.5), glm::vec3(0.5, -1, 0.5), glm::vec3(0, -1, 0),
    glm::vec3(0.5, 0, 0.5), glm::vec3(1, 0, 1), glm::vec3(0.5, 0.5, 0.5),
    glm::vec3(1, 0, 1), glm::vec3(1, 0.5, 1), glm::vec3(0.5, 0.5, 0.5),
    glm::vec3(0.5, -0.5, 0.5), glm::vec3(1, -0.5, 1), glm::vec3(0.5, 0, 0.5),
    glm::vec3(1, -0.5, 1), glm::vec3(1, 0, 1), glm::vec3(0.5, 0, 0.5),
    glm::vec3(0.5, -1, 0.5), glm::vec3(1, -1, 1), glm::vec3(0.5, -0.5, 0.5),
    glm::vec3(1, -1, 1), glm::vec3(1, -0.5, 1), glm::vec3(0.5, -0.5, 0.5),
    glm::vec3(0.5, -1.5, 0.5), glm::vec3(1, -1.5, 1), glm::vec3(0.5, -1, 0.5),
    glm::vec3(1, -1.5, 1), glm::vec3(1, -1, 1), glm::vec3(0.5, -1, 0.5),
    glm::vec3(1, 0, 1), glm::vec3(1.5, 0, 1.5), glm::vec3(1, 0.5, 1),
    glm::vec3(1.5, 0, 1.5), glm::vec3(1.5, 0.5, 1.5), glm::vec3(1, 0.5, 1),
    glm::vec3(1, -0.5, 1), glm::vec3(1.5, -0.5, 1.5), glm::vec3(1, 0, 1),
    glm::vec3(1.5, -0.5, 1.5), glm::vec3(1.5, 0, 1.5), glm::vec3(1, 0, 1),
    glm::vec3(1, -1, 1), glm::vec3(1.5, -1, 1.5), glm::vec3(1, -0.5, 1),
    glm::vec3(1.5, -1, 1.5), glm::vec3(1.5, -0.5, 1.5), glm::vec3(1, -0.5, 1),
    glm::vec3(1, -1.5, 1), glm::vec3(1.5, -1.5, 1.5), glm::vec3(1, -1, 1),
    glm::vec3(1.5, -1.5, 1.5), glm::vec3(1.5, -1, 1.5), glm::vec3(1, -1, 1),
    glm::vec3(1.5, 0, 1.5), glm::vec3(2, 0, 2), glm::vec3(1.5, 0.5, 1.5),
    glm::vec3(2, 0, 2), glm::vec3(2, 0.5, 2), glm::vec3(1.5, 0.5, 1.5),
    glm::vec3(1.5, -0.5, 1.5), glm::vec3(2, -0.5, 2), glm::vec3(1.5, 0, 1.5),
    glm::vec3(2, -0.5, 2), glm::vec3(2, 0, 2), glm::vec3(1.5, 0, 1.5),
    glm::vec3(1.5, -1, 1.5), glm::vec3(2, -1, 2), glm::vec3(1.5, -0.5, 1.5),
    glm::vec3(2, -1, 2), glm::vec3(2, -0.5, 2), glm::vec3(1.5, -0.5, 1.5),
    glm::vec3(1.5, -1.5, 1.5), glm::vec3(2, -1.5, 2), glm::vec3(1.5, -1, 1.5),
    glm::vec3(2, -1.5, 2), glm::vec3(2, -1, 2), glm::vec3(1.5, -1, 1.5),
    glm::vec3(2, 0, 2), glm::vec3(2.5, 0, 2.5), glm::vec3(2, 0.5, 2),
    glm::vec3(2.5, 0, 2.5), glm::vec3(2.5, 0.5, 2.5), glm::vec3(2, 0.5, 2),
    glm::vec3(2, -0.5, 2), glm::vec3(2.5, -0.5, 2.5), glm::vec3(2, 0, 2),
    glm::vec3(2.5, -0.5, 2.5), glm::vec3(2.5, 0, 2.5), glm::vec3(2, 0, 2),
    glm::vec3(2, -1, 2), glm::vec3(2.5, -1, 2.5), glm::vec3(2, -0.5, 2),
    glm::vec3(2.5, -1, 2.5), glm::vec3(2.5, -0.5, 2.5), glm::vec3(2, -0.5, 2),
    glm::vec3(2, -1.5, 2), glm::vec3(2.5, -1.5, 2.5), glm::vec3(2, -1, 2),
    glm::vec3(2.5, -1.5, 2.5), glm::vec3(2.5, -1, 2.5), glm::vec3(2, -1, 2),
    glm::vec3(2.5, 0, 2.5), glm::vec3(3, 0, 3), glm::vec3(2.5, 0.5, 2.5),
    glm::vec3(3, 0, 3), glm::vec3(3, 0.5, 3), glm::vec3(2.5, 0.5, 2.5),
    glm::vec3(2.5, -0.5, 2.5), glm::vec3(3, -0.5, 3), glm::vec3(2.5, 0, 2.5),
    glm::vec3(3, -0.5, 3), glm::vec3(3, 0, 3), glm::vec3(2.5, 0, 2.5),
    glm::vec3(2.5, -1, 2.5), glm::vec3(3, -1, 3), glm::vec3(2.5, -0.5, 2.5),
    glm::vec3(3, -1, 3), glm::vec3(3, -0.5, 3), glm::vec3(2.5, -0.5, 2.5),
    glm::vec3(2.5, -1.5, 2.5), glm::vec3(3, -1.5, 3), glm::vec3(2.5, -1, 2.5),
    glm::vec3(3, -1.5, 3), glm::vec3(3, -1, 3), glm::vec3(2.5, -1, 2.5)

            glm::vec3(0, 0, 0), glm::vec3(0.5, 0, 0.5), glm::vec3(0, 0.5, 0),
            glm::vec3(0.5, 0, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0, 0.5, 0),
            glm::vec3(0, -0.5, 0), glm::vec3(0.5, -0.5, 0.5), glm::vec3(0, 0, 0),
            glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.5, 0, 0.5), glm::vec3(0, 0, 0),
            glm::vec3(0, -1, 0), glm::vec3(0.5, -1, 0.5), glm::vec3(0, -0.5, 0),
            glm::vec3(0.5, -1, 0.5), glm::vec3(0.5, -0.5, 0.5), glm::vec3(0, -0.5, 0),
            glm::vec3(0.5, 0, 0.5), glm::vec3(1, 0, 1), glm::vec3(0.5, 0.5, 0.5),
            glm::vec3(1, 0, 1), glm::vec3(1, 0.5, 1), glm::vec3(0.5, 0.5, 0.5),
            glm::vec3(0.5, -0.5, 0.5), glm::vec3(1, -0.5, 1), glm::vec3(0.5, 0, 0.5),
            glm::vec3(1, -0.5, 1), glm::vec3(1, 0, 1), glm::vec3(0.5, 0, 0.5),
            glm::vec3(0.5, -1, 0.5), glm::vec3(1, -1, 1), glm::vec3(0.5, -0.5, 0.5),
            glm::vec3(1, -1, 1), glm::vec3(1, -0.5, 1), glm::vec3(0.5, -0.5, 0.5),
            glm::vec3(1, 0, 1), glm::vec3(1.5, 0, 1.5), glm::vec3(1, 0.5, 1),
            glm::vec3(1.5, 0, 1.5), glm::vec3(1.5, 0.5, 1.5), glm::vec3(1, 0.5, 1),
            glm::vec3(1, -0.5, 1), glm::vec3(1.5, -0.5, 1.5), glm::vec3(1, 0, 1),
            glm::vec3(1.5, -0.5, 1.5), glm::vec3(1.5, 0, 1.5), glm::vec3(1, 0, 1),
            glm::vec3(1, -1, 1), glm::vec3(1.5, -1, 1.5), glm::vec3(1, -0.5, 1),
            glm::vec3(1.5, -1, 1.5), glm::vec3(1.5, -0.5, 1.5), glm::vec3(1, -0.5, 1)
    };
    std::vector<glm::vec3> a ((0.0,0.0,0.0), (0.0,0.0,0.0));
    m_PointsPtr->m_ppos= std::vector<glm::vec3> (point, point + sizeof(point)/sizeof(glm::vec3));
    */
}

void PBDobj::runSolver(float dt)
{
    //Predict Location

    //update constraints

    //update position
}
