#include <iostream>
#include <memory>
#include <functional>

#include "Core/GLHeaders.h"
#include "Core/Window.h"

#include "Scene/GameSceneController.h"
#include "Scene/GameScene_Title.h"
#include "Scene/GameScene_Play.h"
#include "Scene/GameScene_Clear.h"
#include "Scene/GameScene_Over.h"

#include "Input/InputSystem.h"

GameSceneController::GameSceneController(Window* window_) 
:currentScene(nullptr), window(window_)
{
    // 各ゲームシーンをcontrollerに追加
    addScene(SceneType::Title, std::make_unique<TitleScene>(this, window));
    addScene(SceneType::Play, std::make_unique<PlayScene>(this, window));
    addScene(SceneType::GameOver, std::make_unique<GameOverScene>(this, window));
    addScene(SceneType::Clear, std::make_unique<ClearScene>(this, window));

    // 最初のシーンをタイトルシーンに設定
    ChangeScene(SceneType::Title);
    currentSceneType = SceneType::Title;
}

GameSceneController::~GameSceneController()
{

}

void GameSceneController::addScene(SceneType type, std::unique_ptr<GameScene> scene)
{
    scenes[type] = std::move(scene); //シーンを追加
}

void GameSceneController::ChangeScene(SceneType type)
{
    // currentSceneが前にセットされているならば出口処理
    if(currentScene) { currentScene->Exit(); }

    // シーンが見つからなければ早期リターン
    auto it = scenes.find(type);
    if(it == scenes.end())
    {
        std::cout << "Scene not found!\n";
        return;
    }

    // シーンが見つかれば変更する
    currentScene = it->second.get();
    currentSceneType = it->first;

    // 入口処理
    currentScene->Enter();
}

void GameSceneController::InputGameScene()
{
    currentScene->HandleInput();
    window->LastUpdate();
}

void GameSceneController::UpdateGameScene(float deltaTime)
{
    // 現在設定されているシーンを更新
    currentScene->Update(deltaTime);
}

void GameSceneController::RenderGameScene()
{
    currentScene->Render();
}