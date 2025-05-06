#ifndef OBJECTINFO_H
#define OBJECTINFO_H

#include "GLHeaders.h"
#include "Math/Transform.h"

enum class ObjectType
{
    CUBE,
    FLOOR,
    PYRAMID,
    PLAYER
};

struct ObjectInfo
{
    int id;
    Transform transform;
    glm::vec3 color;
};


#endif /* OBJECTINFO_H */