#ifndef TEST_H
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

bool aproximateVec3(glm::vec3 a, glm::vec3 b, float dif);

//---------------------------------Point stuff-----------------------------

class Point
{
public:
    Point(glm::vec3 _pos,glm::vec3 _pvel , float _pmass);
    ~Point();
    void update();

    float m_pmass;         //vector storing point masses
    glm::vec3 m_ppos;      //vector storing point positions
    glm::vec3 m_pvel;      //vector storing point velocities


private:
};

//---------------------------------Constraint stuff------------------------

class DistanceConstraint
{
public:
    DistanceConstraint(Point* _pA, Point* _pB);
    ~DistanceConstraint();

    virtual void update();
    Point* m_pA;
    Point* m_pB;
    float m_restLength;
};

class BendingConstraint
{
public:
    BendingConstraint(Point* _pA, Point* _pB, Point* _pC);
    ~BendingConstraint();

    virtual void update();
    Point* m_pA;
    Point* m_pB;
    Point* m_pC;
    float m_restAngle;
};

//--------------------------------One class to rule them all----------------

class PBDobj
{
public:
    PBDobj();
    ~PBDobj();

    void addConstraint(DistanceConstraint *m_Constraint);
    void initialize(glm::vec3 _pos,int _width, int _height, float _patchsize);
    void runSolver(float dt);
    int m_width;
    int m_height;
    float m_patchsize;
    std::vector<Point*> m_PointsPtr;
    std::vector<DistanceConstraint *> m_ConPtrs;
};

class PBDtoGLobj
{
public:

    struct triPointer
    {
        Point* p1;
        Point* p2;
        Point* p3;
    };
    PBDtoGLobj(PBDobj* _PBDobj){m_PBDObj=_PBDobj;}
    ~PBDtoGLobj();

    PBDobj* m_PBDObj;
    std::vector<triPointer> GLpoints;
};

#endif // TEST_H
