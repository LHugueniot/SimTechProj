#ifndef CLOTHSIMLIB_H
#define CLOTHSIMLIB_H

#include "clothsimlib_global.h"
class CLOTHSIMLIBSHARED_EXPORT ClothSim
{

public:
    ClothSim(int _width, int _length, float _patchsize);
    ~ClothSim();

    float PointMass(int _vecindex)      const;
    glm::vec3 PointPos(int _vecindex)   const;
    glm::vec3 PointVel(int _vecindex)   const;

    void setPointMass(int _vecindex,float _mass);
    void setPointPos(int _vecindex, glm::vec3 _pos);
    void setPointVel(int _vecindex, glm::vec3 _vel);

    int m_width;
    int m_length;
    float m_initpatchsize;
    std::vector<float> m_pmass;      //vector storing point masses
    std::vector<glm::vec3> m_ppos;   //vector storing point positions
    std::vector<glm::vec3> m_pvel;   //vector storing point velocities

private:

};

#endif // CLOTHSIMLIB_H
