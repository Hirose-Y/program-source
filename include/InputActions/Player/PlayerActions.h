#ifndef PLAYERACTIONS_H
#define PLAYERACTIONS_H

#include "GLHeaders.h"
#include "Input/InputSystem.h"

class PlayerActions
{
public:
    PlayerActions(InputSystem& input_);
    ~PlayerActions();

    // 移動・ジャンプ
    glm::vec3 GetMoveDirection(const glm::vec3& forward, const glm::vec3& right) const;
    bool ShouldJump() const;

private:
    InputSystem input;
};

#endif /* PLAYERACTIONS_H */