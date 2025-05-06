#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "GLHeaders.h"

#include "Game.h"
#include "Window.h"
#include "Scene/GameSceneController.h"

Game::Game()
:mIsRunning(true), lastFrameTime(0), controller(nullptr)
{
    
}

Game::~Game()
{

}

bool Game::Initialize()
{
    window = std::make_unique<Window>(800, 600, "Spin World");

    controller = std::make_unique<GameSceneController>(window.get());
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
