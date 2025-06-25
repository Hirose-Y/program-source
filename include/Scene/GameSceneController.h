#ifndef GAMESCENECONTROLLER_H
#define GAMESCENECONTROLLER_H

#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <unordered_map>

#include "Scene/SceneType.h"
#include "Scene/GameScene.h"

class Window;
class AppContext;


class GameSceneController
{
public:
    GameSceneController(Window* window_, AppContext* context_);
    ~GameSceneController();
    
    //シーンを追加
    void addScene(SceneType type, std::unique_ptr<GameScene> scene);
    // シーンを変更
    void ChangeScene(SceneType type);

    void InputGameScene();
    // シーンを更新
    void UpdateGameScene(float deltaTime);

    void RenderGameScene();

    SceneType GetSceneType() const { return currentSceneType; }
    AppContext* GetContext() { return context; }
private:
    std::unordered_map<SceneType, std::unique_ptr<GameScene>> scenes;   //SceneTypeをキーにしてGameSceneを管理

    Window* window;
    AppContext* context;

    GameScene* currentScene;
    SceneType currentSceneType;
};

#endif /* GAMESCENECONTROLLER_H */