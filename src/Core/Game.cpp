#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "Core/GLHeaders.h"

#include "Core/Game.h"
#include "Core/Window.h"
#include "Core/AppContext.h"
#include "Managers/SoundManager.h"
#include "Scene/GameSceneController.h"

Game::Game()
:mIsRunning(true), lastFrameTime(0), controller(nullptr), context(std::make_unique<AppContext>())
{
    window = std::make_unique<Window>(800, 600, "Spin World");
    context->sound = std::move(std::make_unique<SoundManager>());
}

Game::~Game()
{

}

bool Game::Initialize()
{
    if(!context->sound->Initialize()) return false;

    controller = std::make_unique<GameSceneController>(window.get(), context.get());
    return true;
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    if(!(*window)){
        mIsRunning = false;
    }

    controller->InputGameScene();
}

void Game::UpdateGame()
{
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;

    //ウィンドウの位置移動時に対する処方箋
    deltaTime = std::min(deltaTime, 0.03f);
    //std::cout << "[Game] deltaTime : " << deltaTime << std::endl;

    window->LastUpdate();
    controller->UpdateGameScene(deltaTime);
}

void Game::GenerateOutput()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 画面クリア
    
    controller->RenderGameScene();

    window->swapBuffers();
}

void Game::Shutdown()
{
    
}
