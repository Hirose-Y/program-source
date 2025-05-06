#include <iostream>
#include <memory>
#include "GLHeaders.h"
#include "Scene/GameSceneController.h"
#include "Scene/GameScene_Title.h"
#include "Scene/GameScene_Play.h"
#include "Scene/GameScene_Clear.h"
#include "Scene/GameScene_Over.h"
#include "Shader.h"
#include "Window.h"
#include "Image.h"

#include "Input/InputSystem.h"
#include "InputActions/Context/InputContext_Clear.h"

ClearScene::ClearScene(GameSceneController* controller_, Window* window_)
:GameScene(controller_), window(window_)
{
    shader = std::make_unique<Shader>("Shaders/vert2D.vert", "Shaders/frag2D.frag");
    toTilteimage = std::make_unique<Image>("Assets/image/EntertoTitle.png");
    gameclearImage = std::make_unique<Image>("Assets/image/GameClear.png");
}

ClearScene::~ClearScene()
{

}

void ClearScene::Enter()
{

}

void ClearScene::HandleInput()
{
    auto& input = window->GetInputSystem();
    ClearInputActions action(input);

    SceneType next;
    if(action.scene.ShouldChangeSceneTo(next))
    {
        GameScene::requestSceneChange(next);
    }
}

void ClearScene::Update(float deltaTime)
{

}

void ClearScene::Render()
{
    shader->use();

    glm::vec2 position = glm::vec2(window->GetWidth() * 0.5f, window->GetHeight() * 0.6f);
    glm::vec2 scale = glm::vec2(window->GetWidth() * 0.5f , window->GetHeight() * 0.3);
    gameclearImage->draw(shader.get(), position, scale);

    position = glm::vec2(400, 100);
    scale = glm::vec2(400, 100);
    toTilteimage->draw(shader.get(), position, scale);
}

void ClearScene::Exit()
{

}
