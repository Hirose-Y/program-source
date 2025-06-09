#include "Input/InputSystem.h"
#include "InputActions/Transition/SceneChangeActionsInPlay.h"
#include "Core/GLHeaders.h"
#include "Scene/SceneType.h"
#include <iostream>

SceneChangeActionsInPlay::SceneChangeActionsInPlay(InputSystem& input_)
:input(input_)
{

}

SceneChangeActionsInPlay::~SceneChangeActionsInPlay()
{

}

bool SceneChangeActionsInPlay::ShouldChangeSceneTo(SceneType& outType)
{
    auto& Keyboard = input.GetKeyboard();    //キーボード入力

    #ifdef DEBUG_MODE  //デバック用
        if (Keyboard.IsKeyPressedOnce(GLFW_KEY_T)) {
            std::cout << "[Class::SceneChangeActionsInPlay] : Pressed T_key" << std::endl;
            outType = SceneType::Title;
            return true;
        }
        if (Keyboard.IsKeyPressedOnce(GLFW_KEY_C)) {
            std::cout << "[Class::SceneChangeActionsInPlay] : Pressed C_key" << std::endl;
            outType = SceneType::Clear;
            return true;
        }
        if (Keyboard.IsKeyPressedOnce(GLFW_KEY_O)) {
            std::cout << "[Class::SceneChangeActionsInPlay] : Pressed O_key" << std::endl;
            outType = SceneType::GameOver;
            return true;
        }
        return false;
    #endif

    return false;
}
