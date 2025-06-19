#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <string>
#include "Core/GLHeaders.h"

class Transform
{
public:
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat orientation;

    Transform() = default;

    glm::mat4 getModelMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 translateMatrix = glm::translate(model, position);
        glm::mat4 rotateMatrix = glm::toMat4(orientation);
        glm::mat4 scaleMatrix = glm::scale(model, scale);

        return translateMatrix * rotateMatrix * scaleMatrix;
    }
};

#endif /* TRANSFORM_H */