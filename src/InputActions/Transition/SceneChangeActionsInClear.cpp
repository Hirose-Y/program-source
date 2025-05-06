#include "Input/InputSystem.h"
#include "InputActions/Transition/SceneChangeActionsInClear.h"
#include "GLHeaders.h"
#include "Scene/SceneType.h"
#include <iostream>

SceneChangeActionsInClear::SceneChangeActionsInClear(InputSystem& input_)
:input(input_)
{

}

SceneChangeActionsInClear::~SceneChangeActionsInClear()
{

}

bool SceneChangeActionsInClear::ShouldChangeSceneTo(SceneType& outType)
{
    auto& Keyboard = input.GetKeyboard();    //キーボード入力
    auto& pad = input.GetGamePad();    //ゲームパッド入力

    if (Keyboard.IsKeyPressedOnce(GLFW_KEY_ENTER) || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_DPAD_UP)) {
        #ifdef DEBUG_MODE
        std::cout << "[Class::SceneChangeActionsInClear] : Pressed UP" << std::endl;
        #endif
        outType = SceneType::Title;
        return true;
    }

    if (Keyboard.IsKeyPressedOnce(GLFW_KEY_R) || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_DPAD_DOWN)) {
        #ifdef DEBUG_MODE
        std::cout << "[Class::SceneChangeActionsInClear] : Pressed DOWN" << std::endl;
        #endif
        outType = SceneType::Play;
        return true;
    }

    return false;
}