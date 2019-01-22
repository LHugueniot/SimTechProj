#ifndef POINT_H
#define POINT_H
#include <clothsimlib_global.h>

namespace PBD {

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

}

#endif // POINT_H
