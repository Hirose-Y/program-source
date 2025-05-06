#include "Input/InputSystem.h"
#include "InputActions/Player/PlayerActions.h"
#include "GLHeaders.h"

PlayerActions::PlayerActions(InputSystem& input_)
:input(input_)
{

}

PlayerActions::~PlayerActions()
{

}

glm::vec3 PlayerActions::GetMoveDirection(const glm::vec3& forward, const glm::vec3& right) const
{
    glm::vec3 move(0.0f);
    auto& keyboard = input.GetKeyboard();
    auto& pad = input.GetGamePad();

    // キーボード入力
    if (keyboard.IsKeyPressed(GLFW_KEY_W) || pad.IsButtonPressed(GLFW_GAMEPAD_BUTTON_DPAD_UP))
    {
        move += forward;
    }

    if (keyboard.IsKeyPressed(GLFW_KEY_S) || pad.IsButtonPressed(GLFW_GAMEPAD_BUTTON_DPAD_DOWN))
    {
        move -= forward;
    }

    if (keyboard.IsKeyPressed(GLFW_KEY_D) || pad.IsButtonPressed(GLFW_GAMEPAD_BUTTON_DPAD_RIGHT))
    {
        move += right;
    }

    if (keyboard.IsKeyPressed(GLFW_KEY_A) || pad.IsButtonPressed(GLFW_GAMEPAD_BUTTON_DPAD_LEFT))
    {
        move -= right;
    }

    // パッド入力
    float x = pad.GetAxis(0);
    float y = pad.GetAxis(1);
    if (fabs(x) > 0.2f || fabs(y) > 0.2f) {
        move += right * x + forward * (-y);
    }

    return move;    
}

bool PlayerActions::ShouldJump() const
{
    auto& keyboard = input.GetKeyboard();
    auto& pad = input.GetGamePad();

    if(keyboard.IsKeyPressed(GLFW_KEY_SPACE) || pad.IsButtonPressed(GLFW_GAMEPAD_BUTTON_A))
    // xboxのコントローラーならA、スイッチやPSのコントローラーならB
    {
        return true;
    }

    return false;
}
