#ifndef WORLDACTIONS_H
#define WORLDACTIONS_H

#include "GLHeaders.h"
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
    InputSystem input;
};

#endif /* WORLDACTIONS_H */