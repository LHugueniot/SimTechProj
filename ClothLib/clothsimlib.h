#ifndef CLOTHSIMLIB_H
#define CLOTHSIMLIB_H

#include "clothsimlib_global.h"

namespace PBD {

struct Tri
{
    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 c;
};

Tri makeTriangle(glm::vec3 _pos, float _patchsize);
Tri triMirror(Tri _patch,float _patchsize );

class CLOTHSIMLIBSHARED_EXPORT ClothSim
{

public:

    ClothSim();
    ~ClothSim();

    float PointMass(int _vecindex)      const;  //get point mass
    glm::vec3 PointPos(int _vecindex)   const;  //get point position
    glm::vec3 PointVel(int _vecindex)   const;  //get point velocity

    void setPointMass(int _vecindex,float _mass);       //set point mass
    void setPointPos(int _vecindex, glm::vec3 _pos);    //set point position
    void setPointVel(int _vecindex, glm::vec3 _vel);    //set point velocity

    void makeSmolMesh(glm::vec3 _pos, float _patchsize);
    void makeMesh(glm::vec3 _pos,int _width, int _height, float _patchsize);

    int m_width;                        //cloth width (in vertices)
    int m_height;                       //cloth length  (in vertices)
    int m_pnum;                         //total number of points in cloth
    float m_initpatchsize;              //base distance between each point

    std::vector<float> m_pmass;         //vector storing point masses
    std::vector<glm::vec3> m_ppos;      //vector storing point positions
    std::vector<glm::vec3> m_pvel;      //vector storing point velocities


private:

};

}

#endif // CLOTHSIMLIB_H
