#include <iostream>
#include <memory>
#include <string>

#include "Shader.h"
#include "Image.h"

#include "Scene/GameSceneController.h"
#include "Scene/GameScene_Title.h"
#include "Scene/GameScene_Play.h"
#include "Scene/GameScene_Clear.h"
#include "Scene/GameScene_Over.h"

#include "Stage/Stage.h"

#include "Input/InputSystem.h"
#include "InputActions/Context/InputContext_Play.h"

PlayScene::PlayScene(GameSceneController* controller_, Window* window_)
:GameScene(controller_), window(window_)
{
    pause = false;
    pauseMode = 0;
    shader2D = std::make_unique<Shader>("Shaders/vert2D.vert", "Shaders/frag2D.frag");
    UIInfo_Pad = std::make_unique<Image>("Assets/image/info_pad.png");
    UIInfo_Key = std::make_unique<Image>("Assets/image/info_key.png");
}

PlayScene::~PlayScene()
{
    
}

void PlayScene::Initialize()
{
    stage = std::make_unique<Stage>(window);
    stage->SetStage("Assets/stage/floors.json", "Assets/stage/sticks.json", "Assets/stage/pyramids.json");
}

void PlayScene::Enter()
{
    Initialize();
}

void PlayScene::HandleInput()
{
    auto& input = window->GetInputSystem();
    PlayInputActions action(input);

    SceneType next;
    if(action.scene.ShouldChangeSceneTo(next))
    {
        GameScene::requestSceneChange(next);
    }
    pauseMode = action.ShowInfomation(pause, pauseMode);

    stage->HandleInput(input); 
}

void PlayScene::Update(float deltaTime)
{
    if(pause) { return; }

    if(stage->isClear())
    {
        GameScene::requestSceneChange(SceneType::Clear);
    }

    if(stage->isGameOver())
    {
        GameScene::requestSceneChange(SceneType::GameOver);
    }

    stage->Update(deltaTime);
}

void PlayScene::Render()
{
    if(pause) {
        //UIの描画（ピラミッドの画像）
        shader2D->use();
        glm::vec2 position = glm::vec2(window->GetWidth() / 2, window->GetHeight() /2);
        glm::vec2 scale = glm::vec2(window->GetWidth() / 2, window->GetHeight() / 2);
        if (pauseMode == 0) {
            UIInfo_Pad->draw(shader2D.get(), position, scale);
        } else if (pauseMode == 1) {
            UIInfo_Key->draw(shader2D.get(), position, scale);
        }

        return;
    }

    stage->Render();
}

void PlayScene::Exit()
{
    stage->Clear();
}