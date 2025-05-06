#ifndef CAMERAACTIONS_H
#define CAMERAACTIONS_H

#include "GLHeaders.h"
#include "Input/InputSystem.h"

class CameraActions
{
public:
    CameraActions(InputSystem& input_);
    ~CameraActions();

    // ヨーの回転
    bool ShouldRotationYaw(float& yawInput) const;

    bool ShouldRotationPitch(float& yawInput) const;

    bool ResetYawAndPitch() const;
private:
    InputSystem input;
};

#endif /* CAMERAACTIONS_H */