#include "Input/InputSystem.h"
#include "InputActions/Context/InputContext_Play.h"

PlayInputActions::PlayInputActions(InputSystem& input_)
:input(input_), scene(input_), player(input_), world(input_), camera(input_)
{
    
}

int PlayInputActions::ShowInfomation(bool& pause, int& mode) const
{
    auto& keyboard = input.GetKeyboard();
    auto& pad = input.GetGamePad();

    if(keyboard.IsKeyPressedOnce(GLFW_KEY_I) || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_Y))
    {
        if(!pause)
        {
            pause = true;
        }else{
            pause = false;
        }
    }

    bool presskeys = keyboard.IsKeyPressedOnce(GLFW_KEY_ENTER) || keyboard.IsKeyPressedOnce(GLFW_KEY_SPACE)
                        || keyboard.IsKeyPressedOnce(GLFW_KEY_RIGHT) || keyboard.IsKeyPressedOnce(GLFW_KEY_LEFT);

    bool presspads = pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_X) || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_DPAD_RIGHT)
                        || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_DPAD_LEFT) || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_A);
    if(pause)
    {
        if(presskeys || presspads)
        {
            mode++;
            mode = mode % 2;
        }
    }

    return mode;
}
