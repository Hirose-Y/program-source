#ifndef LIGHT_H
#define LIGHT_H

#include <string>
#include "Core/GLHeaders.h"

class Light
{
public:
    glm::vec3 position;
    glm::vec3 lightColor;
    glm::vec3 lightDir;
};

#endif /* LIGHT_H */