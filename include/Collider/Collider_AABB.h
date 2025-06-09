#ifndef COLLIDER_AABB_H
#define COLLIDER_AABB_H

#include <string>
#include "Core/GLHeaders.h"
#include "Collider/Collider.h"
#include "Collider/ColliderType.h"

class AABB : public Collider
{
public:
    AABB(const glm::mat4 model);

    void Update(const glm::mat4 model) override;

    bool checkCollision(const Collider& other) const override;
    glm::vec3 resolveCollision(const Collider& other) override;

    ColliderType getType() const override { return ColliderType::AABB; }
    glm::vec3 Center() const { return center; }
    glm::vec3 HalfSize() const { return halfSize; }

private:
    glm::vec3 center;
    glm::vec3 halfSize;

    // model変換用
    glm::vec3 extractedScale;         // スケール（拡大縮小の値）
    glm::quat orientation;            // 回転（クォータニオン）
    glm::vec3 extractedTranslation;   // 位置（移動量）
    glm::vec3 skew;                   // せん断（shear、ねじれ）
    glm::vec4 perspective;            // 透視変換成分（透視投影用）
};

#endif /* COLLIDER_AABB_H */