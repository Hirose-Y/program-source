#ifndef PLAYERACTIONS_H
#define PLAYERACTIONS_H

#include <string>
#include "Core/GLHeaders.h"
#include "Input/InputSystem.h"

class PlayerActions
{
public:
    PlayerActions(InputSystem& input_);
    ~PlayerActions();

    // 移動・ジャンプ
    glm::vec3 GetMoveDirection(const glm::vec3& forward, const glm::vec3& right) const;
    bool ShouldJump() const;

    // 向き制御(yaw)
    bool ShouldRotationYaw(float& yawInput) const;

private:
    InputSystem input;
};

#endif /* PLAYERACTIONS_H */