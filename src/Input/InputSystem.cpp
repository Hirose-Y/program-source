#include "Input/InputSystem.h"
#include <iostream>

InputSystem::InputSystem()
:gamePad(GLFW_JOYSTICK_1)
{
    #ifdef DEBUG_MODE
    if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
        std::cout << "Joystick 1 is connected: " << glfwGetJoystickName(GLFW_JOYSTICK_1) << std::endl;
    }

    if (glfwJoystickIsGamepad(GLFW_JOYSTICK_1)) {
        std::cout << "Gamepad OK!" << std::endl;
    } else {
        std::cout << "Not a gamepad..." << std::endl;
    }
    #endif
}

InputSystem::~InputSystem()
{
    
}

void InputSystem::Update()
{
    keyboard.UpdateKeyState();

    gamePad.Update();
}

void InputSystem::OnKeyEvent(int key, int action) {
    keyboard.ProcessKeyEvent(key, action);
}