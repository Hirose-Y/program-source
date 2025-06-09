#include "Input/GamePad.h"
#include "Core/GLHeaders.h"
#include <cstring>

GamePad::GamePad(int id) : joystickId(id) {
    std::memset(prevButtons, 0, sizeof(prevButtons));
}

bool GamePad::IsConnected() const {
    return glfwJoystickPresent(joystickId);
}

float GamePad::GetAxis(int axis) const {
    if (!IsConnected()) return 0.0f;

    int count;
    const float* axes = glfwGetJoystickAxes(joystickId, &count);
    return (axes && axis < count) ? axes[axis] : 0.0f;
}

bool GamePad::IsButtonPressed(int button) const {
    if (!IsConnected() || !glfwJoystickIsGamepad(joystickId)) return false;

    GLFWgamepadstate state;
    if (glfwGetGamepadState(joystickId, &state)) {
        return state.buttons[button] == GLFW_PRESS;
    }
    return false;
}

bool GamePad::IsButtonPressedOnce(int button) const {
    if (!IsConnected() || !glfwJoystickIsGamepad(joystickId)) return false;

    GLFWgamepadstate state;
    if (glfwGetGamepadState(joystickId, &state)) {
        bool pressedNow = state.buttons[button] == GLFW_PRESS;
        bool pressedBefore = prevButtons[button] == GLFW_PRESS;
        return !pressedBefore && pressedNow;
    }
    return false;
}

bool GamePad::IsAnyButtonPressed() const {
    if (!IsConnected() || !glfwJoystickIsGamepad(joystickId)) return false;

    GLFWgamepadstate state;
    if (glfwGetGamepadState(joystickId, &state)) {
        for (int i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST; ++i) {
            if (state.buttons[i] == GLFW_PRESS) {
                return true;
            }
        }
    }
    return false;
}

bool GamePad::IsAnyButtonPressedOnce() const {
    if (!IsConnected() || !glfwJoystickIsGamepad(joystickId)) return false;

    GLFWgamepadstate state;
    if (glfwGetGamepadState(joystickId, &state)) {
        for (int i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST; ++i) {
            if (state.buttons[i] == GLFW_PRESS && prevButtons[i] != GLFW_PRESS) {
                return true;
            }
        }
    }
    return false;
}

void GamePad::Update() {
    if (!IsConnected() || !glfwJoystickIsGamepad(joystickId)) return;

    GLFWgamepadstate state;
    if (glfwGetGamepadState(joystickId, &state)) {
        std::memcpy(prevButtons, state.buttons, sizeof(prevButtons));
    }
}

