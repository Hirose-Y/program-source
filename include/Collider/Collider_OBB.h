#ifndef COLLIDER_OBB_H
#define COLLIDER_OBB_H

#include "GLHeaders.h"
#include "Collider/Collider.h"
#include "Collider/ColliderType.h"

#include <array>

class OBB : public Collider
{
public:
    OBB(const glm::mat4 model);

    void Update(const glm::mat4 model) override;

    bool checkCollision(const Collider& other) const override;
    glm::vec3 resolveCollision(const Collider& other) override;
    bool testAxis(const glm::vec3& axis, const OBB& a, const OBB& b, const glm::vec3& D) const;
    bool intersectRay(const glm::vec3& origin, const glm::vec3& dir, float& outDistance);

    ColliderType getType() const override { return ColliderType::OBB; }
    glm::mat4 GetModelMatrix() const { return modelMatrix; }
    glm::mat4 GetPrevModel() const { return prevModelMatrix; }
    glm::vec3 Center() const { return center; }
    glm::vec3 HalfSize() const { return halfSizes; }

    glm::vec3 axes[3]; // 各軸の方向ベクトル
    glm::vec3 previousCenter;
private:

    glm::mat4 modelMatrix;
    glm::mat4 prevModelMatrix;

    glm::vec3 center;

    glm::vec3 halfSizes;
    
    glm::mat3 rotation;
    // model変換用
    glm::vec3 extractedScale;         // スケール（拡大縮小の値）
    glm::quat orientation;            // 回転（クォータニオン）
    glm::vec3 extractedTranslation;   // 位置（移動量）
    glm::vec3 skew;                   // せん断（shear、ねじれ）
    glm::vec4 perspective;            // 透視変換成分（透視投影用）
};

#endif /* COLLIDER_OBB_H */