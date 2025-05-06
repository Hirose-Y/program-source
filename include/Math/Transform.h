#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "GLHeaders.h"

class Transform
{
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform() = default;

    glm::mat4 getModelMatrix() const {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
        glm::vec3 radians = glm::radians(rotation); //degreeをラジアンに変換
        glm::quat q = glm::quat(radians);  // ラジアンをquaternionに変換し、4x4の回転行列に変換
        model *= glm::toMat4(q);
        model = glm::scale(model, scale);
        return model;
    }
};

#endif /* TRANSFORM_H */