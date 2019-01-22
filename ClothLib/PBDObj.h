#ifndef PBDOBJ_H
#define PBDOBJ_H
#include <clothsimlib_global.h>
#include "point.h"
#include "constraints.h"
#include "collisionobj.h"
#include "lml.h"

namespace PBD {

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

#endif // PBDOBJ_H
