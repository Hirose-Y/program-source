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
    glm::vec3 DesideRotationAxis(float angle, bool pressLQ, WorldRotator* rotator) const;

    InputSystem input;
};

#endif /* WORLDACTIONS_H */