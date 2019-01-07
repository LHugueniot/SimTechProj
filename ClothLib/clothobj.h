#ifndef CLOTHOBJ_H
#define CLOTHOBJ_H

#include "clothsimlib.h"

namespace PBD {
class CLOTHSIMLIBSHARED_EXPORT ClothObj : public PBDObj
{
public:
    ClothObj();
    ~ClothObj();
    void makeSmolMesh(glm::vec3 _pos, float _patchsize);
    void makeMesh(glm::vec3 _pos,int _width, int _height, float _patchsize);

    int m_width;                        //cloth width (in vertices)
    int m_height;                       //cloth length  (in vertices)
    int m_pnum;                         //total number of points in cloth
    float m_initpatchsize;              //base distance between each point
};
}
#endif // CLOTHOBJ_H
