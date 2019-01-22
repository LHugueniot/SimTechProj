#ifndef COLLISIONOBJ_H
#define COLLISIONOBJ_H
#include <clothsimlib_global.h>
#include "point.h"
#include "constraints.h"

namespace PBD {

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

}
#endif // COLLISIONOBJ_H
