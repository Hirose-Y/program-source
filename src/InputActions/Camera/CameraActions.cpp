#include "Input/InputSystem.h"
#include "InputActions/Camera/CameraActions.h"
#include "Core/GLHeaders.h"
#include "Scene/SceneType.h"

#include "World/WorldRotator.h"
#include <iostream>


CameraActions::CameraActions(InputSystem& input_)
:input(input_)
{

}

CameraActions::~CameraActions()
{

}

bool CameraActions::ShouldRotationYaw(float& yawInput) const
{
    auto& keyboard = input.GetKeyboard();
    auto& pad = input.GetGamePad();

    if(keyboard.IsKeyPressed(GLFW_KEY_LEFT))
    {
        yawInput -= 0.3f;
    }
    if(keyboard.IsKeyPressed(GLFW_KEY_RIGHT))
    {
        yawInput += 0.3f;
    }

    float lefttrigger = pad.GetAxis(GLFW_GAMEPAD_AXIS_LEFT_TRIGGER);
    if (lefttrigger > 0.2f) yawInput -= lefttrigger;

    float righttrigger = pad.GetAxis(GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER);
    if (righttrigger > 0.2f) yawInput += righttrigger;

    return fabs(yawInput) > 0.01f;
}

bool CameraActions::ShouldRotationPitch(float& pitchInput) const
{
    auto& keyboard = input.GetKeyboard();
    auto& pad = input.GetGamePad();

    if(keyboard.IsKeyPressed(GLFW_KEY_UP))
    {
        pitchInput += 0.3f;
    }
    if(keyboard.IsKeyPressed(GLFW_KEY_DOWN))
    {
        pitchInput -= 0.3f;
    }

    float rightStickY = pad.GetAxis(GLFW_GAMEPAD_AXIS_RIGHT_Y);
    if (fabs(rightStickY) > 0.2f) {
        pitchInput -= rightStickY;
    }

    return fabs(pitchInput) > 0.01f;
}

bool CameraActions::ResetYawAndPitch() const
{
    auto& keyboard = input.GetKeyboard();
    auto& pad = input.GetGamePad();
    
    if (keyboard.IsKeyPressedOnce(GLFW_KEY_X) || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_X))
    {
        return true;
    }

    return false;
}
