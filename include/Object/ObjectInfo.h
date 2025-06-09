#ifndef OBJECTINFO_H
#define OBJECTINFO_H

#include <string>
#include "Core/GLHeaders.h"
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

    bool isTransparency;
    float transparency;
};


#endif /* OBJECTINFO_H */