#include "Input/InputSystem.h"
#include "InputActions/Transition/SceneChangeActionsInTitle.h"
#include "Core/GLHeaders.h"
#include "Scene/SceneType.h"
#include <iostream>

SceneChangeActionsInTitle::SceneChangeActionsInTitle(InputSystem& input_)
:input(input_)
{

}

SceneChangeActionsInTitle::~SceneChangeActionsInTitle()
{

}

bool SceneChangeActionsInTitle::ShouldChangeSceneTo(SceneType& outType)
{
    auto& Keyboard = input.GetKeyboard();    //キーボード入力
    auto& pad = input.GetGamePad();    //ゲームパッド入力

    if (Keyboard.IsKeyPressedOnce(GLFW_KEY_ENTER) || pad.IsAnyButtonPressedOnce()) {
        outType = SceneType::Play;
        return true;
    }

    return false;
}