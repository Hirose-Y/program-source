#ifndef LIGHT_H
#define LIGHT_H

#include "GLHeaders.h"

class Light
{
public:
    glm::vec3 position;
    glm::vec3 lightColor;
    glm::vec3 lightDir;
};

#endif /* LIGHT_H */