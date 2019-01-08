﻿#ifndef TEST_H
#define TEST_H
#include <clothsimlib_global.h>

//--------------------------------Triangle Stuff---------------------------

struct Tri
{
    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 c;
};

Tri makeTriangle(glm::vec3 _pos, float _patchsize);
Tri triMirror(Tri _patch,float _patchsize );


//---------------------------------Point stuff-----------------------------

class Points
{
public:
    Points();
    ~Points();

    float PointMass(int _vecindex)      const;  //get point mass
    glm::vec3 PointPos(int _vecindex)   const;  //get point position
    glm::vec3 PointVel(int _vecindex)   const;  //get point velocity

    void setPointMass(int _vecindex,float _mass);       //set point mass
    void setPointPos(int _vecindex, glm::vec3 _pos);    //set point position
    void setPointVel(int _vecindex, glm::vec3 _vel);    //set point velocity

    std::vector<float> m_pmass;         //vector storing point masses
    std::vector<glm::vec3> m_ppos;      //vector storing point positions
    std::vector<glm::vec3> m_pvel;      //vector storing point velocities


private:
};

class Constraint
{
public:
    Constraint(Points* _points, int _pAindex, int _pBindex, float _pConRes);
    ~Constraint();

    void update();
    Points* points;
    int m_pA;
    int m_pB;
    float restLength;
    float m_pConRes;
};

class PBDobj
{
public:
    PBDobj(std::vector<Constraint *> _ConPtrs, Points* _PointsPtr);
    ~PBDobj();

    void addConstraint(Constraint* m_Constraint);
    void initialize(glm::vec3 _pos,int _width, int _height, float _patchsize);
    void runSolver(float dt);

    Points* m_PointsPtr;
    std::vector<Constraint *> m_ConPtrs;
};
#endif // TEST_H
