#include "Input/InputSystem.h"
#include "InputActions/Transition/SceneChangeActionsInOver.h"
#include "Core/GLHeaders.h"
#include "Scene/SceneType.h"
#include <iostream>

SceneChangeActionsInOver::SceneChangeActionsInOver(InputSystem& input_)
:input(input_)
{

}

SceneChangeActionsInOver::~SceneChangeActionsInOver()
{

}

bool SceneChangeActionsInOver::ShouldChangeSceneTo(SceneType& outType)
{
    auto& Keyboard = input.GetKeyboard();    //キーボード入力
    auto& pad = input.GetGamePad();    //ゲームパッド入力

    if (Keyboard.IsKeyPressedOnce(GLFW_KEY_ENTER) || pad.IsAnyButtonPressedOnce()) {
        #ifdef DEBUG_MODE
        std::cout << "[Class::SceneChangeActionsInOver] : Pressed Button" << std::endl;
        #endif
        outType = SceneType::Play;
        return true;
    }

    return false;
}