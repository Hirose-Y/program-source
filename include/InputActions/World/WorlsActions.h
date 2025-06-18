#ifndef WORLDACTIONS_H
#define WORLDACTIONS_H

#include <string>
#include "Core/GLHeaders.h"
#include "Input/InputSystem.h"

class WorldRotator;

class WorldActions
{
public:
    WorldActions(InputSystem& input_);
    ~WorldActions();

    // ワールドの回転
    bool ShouldStartRotationWorld(WorldRotator& rotator) const;
private:
    void DesideRotationAxis(float angle, bool pressLQ, WorldRotator* rotator) const;

    InputSystem input;

    mutable glm::vec3 rotationAxis; //回転軸
};

#endif /* WORLDACTIONS_H */