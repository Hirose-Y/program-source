#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <string>
#include "Core/GLHeaders.h"

class Transform
{
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform() = default;

    glm::mat4 getModelMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 translateMatrix = glm::translate(model, position);

        glm::vec3 radians = glm::radians(rotation); //degreeをラジアンに変換
        glm::quat q = glm::quat(radians);  // ラジアンをquaternionに変換し、4x4の回転行列に変換
        glm::mat4 rotateMatrix = glm::toMat4(q);

        glm::mat4 scaleMatrix = glm::scale(model, scale);

        glm::mat4 transformMatrix = translateMatrix * rotateMatrix * scaleMatrix;
        return transformMatrix;
    }
};

#endif /* TRANSFORM_H */