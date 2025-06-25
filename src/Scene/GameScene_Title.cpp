#include <iostream>
#include <memory>
#include "Core/GLHeaders.h"
#include "Scene/GameSceneController.h"
#include "Scene/GameScene_Title.h"
#include "Scene/GameScene_Play.h"
#include "Scene/GameScene_Clear.h"
#include "Scene/GameScene_Over.h"
#include "Graphics/Shader.h"
#include "Core/Window.h"
#include "Graphics/Image.h"

#include "Input/InputSystem.h"
#include "InputActions/Context/InputContext_Title.h"

#include "Managers/SoundManager.h"

TitleScene::TitleScene(GameSceneController* controller_, Window* window_)
:GameScene(controller_), window(window_)
{
    shader = std::make_unique<Shader>("Shaders/vert2D.vert", "Shaders/frag2D.frag");
    image = std::make_unique<Image>("Assets/image/EntertoStart.png");
    titleImage = std::make_unique<Image>("Assets/image/Title.png");
}

TitleScene::~TitleScene()
{

}

void TitleScene::Enter()
{   

} 

void TitleScene::HandleInput()
{
    auto& input = window->GetInputSystem();
    TitleInputActions action(input);

    SceneType next;
    if(action.scene.ShouldChangeSceneTo(next))
    {
        GameScene::Context()->sound->PlaySE("ex8_9.wav");
        GameScene::requestSceneChange(next);
    }
}

void TitleScene::Update(float deltaTime)
{
      
}

void TitleScene::Render()
{
    glClearColor(0.3f, 0.8f, 0.2f, 0.0f);

    glm::vec2 position = glm::vec2(window->GetWidth() * 0.5f, window->GetHeight() * 0.6f);
    glm::vec2 scale = glm::vec2(window->GetWidth() * 0.5f , window->GetHeight() * 0.3);
    titleImage->draw(shader.get(), position, scale);

    position = glm::vec2(400, 100);
    scale = glm::vec2(400, 100);
    image->draw(shader.get(), position, scale);
}

void TitleScene::Exit()
{

}