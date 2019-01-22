#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H
#include <clothsimlib_global.h>
#include "point.h"

namespace PBD {

class Constraint
{
    Constraint(){}
    ~Constraint(){}

    virtual void update();
};

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

}

#endif // CONSTRAINTS_H
