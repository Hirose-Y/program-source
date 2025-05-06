#include "Input/InputSystem.h"
#include "InputActions/World/WorlsActions.h"
#include "GLHeaders.h"
#include "Scene/SceneType.h"

#include "World/World.h"
#include "World/WorldRotator.h"
#include <iostream>

#include "Camera/Camera.h"
#include "Utils/Helper.h"

WorldActions::WorldActions(InputSystem& input_)
:input(input_)
{

}

WorldActions::~WorldActions()
{

}

bool WorldActions::ShouldStartRotationWorld(WorldRotator& rotator) const
{
    auto& keyboard = input.GetKeyboard();
    auto& pad = input.GetGamePad();

    const Camera* camera = rotator.GetWorld()->GetCamera();
    glm::vec3 camForward = camera->getCurrentCameraFront();

    camForward = Helper::KeepMaxComponent(camForward);
    Helper::printVec3("WaorldAction", "camF", glm::normalize(camForward));

    if (keyboard.IsKeyPressedOnce(GLFW_KEY_Q) || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_LEFT_BUMPER))
    {
        rotator.StartRotation(1, camForward, 90.0f, 180.0f);
        return true;
    }

    if (keyboard.IsKeyPressedOnce(GLFW_KEY_E) || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER))
    {
        rotator.StartRotation(-1, -camForward, 90.0f, 180.0f);
        return true;
    }

    return false;
}
