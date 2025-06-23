#ifndef CAMERAACTIONS_H
#define CAMERAACTIONS_H

#include <string>
#include "Core/GLHeaders.h"
#include "Input/InputSystem.h"

class CameraActions
{
public:
    CameraActions(InputSystem& input_);
    ~CameraActions();
    
    //　ピッチの回転
    bool ShouldRotationPitch(float& yawInput) const;

    bool ResetYawAndPitch() const;

private:
    InputSystem input;
};

#endif /* CAMERAACTIONS_H */