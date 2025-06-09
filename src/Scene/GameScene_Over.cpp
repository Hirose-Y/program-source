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
#include "InputActions/Context/InputContext_Over.h"

GameOverScene::GameOverScene(GameSceneController* controller_, Window* window_)
:GameScene(controller_), window(window_)
{    
    shader = std::make_unique<Shader>("Shaders/vert2D.vert", "Shaders/frag2D.frag");
    toTilteimage = std::make_unique<Image>("Assets/image/EntertoTitle.png");
    gameoverImage = std::make_unique<Image>("Assets/image/GameOver.png");
}

GameOverScene::~GameOverScene()
{

}

void GameOverScene::Enter()
{

}

void GameOverScene::HandleInput()
{
    auto& input = window->GetInputSystem();
    OverInputActions action(input);

    SceneType next;
    if(action.scene.ShouldChangeSceneTo(next))
    {
        GameScene::requestSceneChange(next);
    }
}

void GameOverScene::Update(float deltaTime)
{
    
}

void GameOverScene::Render()
{
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    shader->use();

    glm::vec2 position = glm::vec2(window->GetWidth() * 0.5f, window->GetHeight() * 0.6f);
    glm::vec2 scale = glm::vec2(window->GetWidth() * 0.5f , window->GetHeight() * 0.3);
    gameoverImage->draw(shader.get(), position, scale);

    position = glm::vec2(400, 100);
    scale = glm::vec2(400, 100);
    toTilteimage->draw(shader.get(), position, scale);
}

void GameOverScene::Exit()
{
    
}

