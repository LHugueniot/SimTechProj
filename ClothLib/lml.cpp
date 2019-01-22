#include "lml.h"

namespace LML {

bool aproximateVec3(glm::vec3 a, glm::vec3 b, float dif)
{
    if(a.x+dif>(b.x) && a.x-dif<(b.x))
    {
        if(a.y+dif>(b.y) && a.y-dif<(b.y))
        {
            if(a.z+dif>(b.z) && a.z-dif<(b.z))
            {
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

}
