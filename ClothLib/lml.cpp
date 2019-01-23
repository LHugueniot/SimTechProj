#include "lml.h"

namespace LML {

bool aproximateVec3(glm::vec3 a, glm::vec3 b, float dif)
{
    return a.x+dif>(b.x) && a.x-dif<(b.x) &&
           a.y+dif>(b.y) && a.y-dif<(b.y) &&
           a.z+dif>(b.z) && a.z-dif<(b.z);
}

}
