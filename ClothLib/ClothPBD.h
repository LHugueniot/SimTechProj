#ifndef TEST_H
#define TEST_H
#include <clothsimlib_global.h>

namespace PBD {


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



//---------------------------------Point Class-----------------------------

class Point
{
public:
    Point(glm::vec3 _pos,glm::vec3 _pvel , float _pmass);
    ~Point();
    void update();
    float m_pmass;          //float storing point masse
    float m_invMass;        //float storing inverse point mass
    glm::vec3 m_ppos;       //vec3 storing point position
    glm::vec3 m_pvel;       //vec3 storing point velocitie
    glm::vec3 tmp_pos;      //vec3 storing predicted point position

};

//-----------------------------------Collision obj classes---------------------

class CollisionObj
{
public:
    CollisionObj(){}
    ~CollisionObj(){}
    virtual void CreateShape(){}
    virtual bool CheckCollision(Point& p){}
    virtual bool CheckCollision1(int k, glm::vec3 _ray){}
    std::vector<glm::vec3> vertices;
    double m_radius;
    glm::vec3 m_pos;
};

class Sphere : public CollisionObj
{
public:
    Sphere(double _radius, glm::vec3 _pos);
    ~Sphere();
    virtual void CreateShape();
    virtual bool CheckCollision(Point& p);
    virtual bool CheckCollision1(int k, glm::vec3 _ray);
};

class Plain : public CollisionObj
{
public:
    Plain(int _width, int _height, glm::vec3 _pos);
    ~Plain();
    virtual void CreateShape();
    virtual bool CheckCollision(Point& p);
    int m_width;
    int m_height;
    int m_depth;
};

//---------------------------------Constraint stuff------------------------

class DistanceConstraint
{
public:
    DistanceConstraint(Point* _pA, Point* _pB);
    ~DistanceConstraint();

    void update();
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

//--------------------------------PBDobj Class--------------------------------------------------

class PBDobj
{
public:
    PBDobj();
    ~PBDobj();

    void addConstraint(DistanceConstraint *m_Constraint);
    void addObjectToList(CollisionObj * _newColObj);
    void initialize(glm::vec3 _pos, int _width, int _height, float _patchsize, float _damping);
    void changePointMass(uint _index, float _newMass){m_PointsPtr[_index]->m_invMass=_newMass;}
    void runSolver(float dt);

    glm::vec3 m_pos;
    int m_width;
    int m_height;
    float m_patchsize;
    float m_damp;
    glm::vec3 m_grav=glm::vec3(0,-0.1,0);

    std::vector<Point*> m_PointsPtr;
    std::vector<DistanceConstraint *> m_ConPtrs;
    std::vector<CollisionObj*> OtherObjs;

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

    void update();
    PBDobj* m_PBDObj;
    std::vector<triPointer> GLpoints;
};
}

#endif // TEST_H
