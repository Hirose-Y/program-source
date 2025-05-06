#include "Input/Keyboard.h"

#include <iostream>

Keyboard::Keyboard()
{

}

Keyboard::~Keyboard()
{

}

void Keyboard::ProcessKeyEvent(int key, int action)
{
    keyStatus[key] = action;
}

void Keyboard::UpdateKeyState()
{
    prevKeyStatus = keyStatus;
}

bool Keyboard::IsKeyPressed(int key) const
{
    auto it = keyStatus.find(key);
    return (it != keyStatus.end()) && (it->second == GLFW_PRESS || it->second == GLFW_REPEAT);
}

bool Keyboard::IsKeyPressedOnce(int key) const
{
    int prev = GLFW_RELEASE;
    if (auto it = prevKeyStatus.find(key); it != prevKeyStatus.end()) {
        prev = it->second;
    }
    int now = GLFW_RELEASE;
    if (auto it = keyStatus.find(key); it != keyStatus.end()) {
        now = it->second;
    }
    return (prev == GLFW_RELEASE && now == GLFW_PRESS);
}

bool Keyboard::IsKeyReleasedOnce(int key) const
{
    int prev = GLFW_RELEASE;
    if (auto it = prevKeyStatus.find(key); it != prevKeyStatus.end()) {
        prev = it->second;
    }
    int now = GLFW_RELEASE;
    if (auto it = keyStatus.find(key); it != keyStatus.end()) {
        now = it->second;
    }
    return (prev == GLFW_PRESS && now == GLFW_RELEASE);
}

#ifdef DEBUG_MODE
void Keyboard::DebugPrintKeyStatus() const
{
    std::cout << "---- KeyStatus Debug ----" << std::endl;
    for (const auto& [key, action] : keyStatus) {
        std::string actionStr;
        switch (action) {
            case GLFW_PRESS:   actionStr = "PRESS"; break;
            case GLFW_RELEASE: actionStr = "RELEASE"; break;
            case GLFW_REPEAT:  actionStr = "REPEAT"; break;
            default:           actionStr = "UNKNOWN"; break;
        }
        std::cout << "Key " << key << " : " << actionStr << std::endl;
    }
    std::cout << "--------------------------" << std::endl;
}
#endif