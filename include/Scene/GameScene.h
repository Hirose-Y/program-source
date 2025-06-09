#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <string>
#include <iostream>
#include <memory>

#include "Scene/SceneType.h"

class GameSceneController;
class Window;
 
//ゲームシーンを表す基底クラス
class GameScene
{
private:
    GameSceneController* controller;  //ゲームシーンコントローラーへのポインタ

public:
    explicit GameScene(GameSceneController* controller_);
    virtual ~GameScene() { };

    virtual void Enter() = 0;   // 入口処理
    virtual void Exit() = 0;    // 出口処理

    virtual void HandleInput() = 0;
    virtual void Update(float deltaTime) = 0;   // 更新処理
    virtual void Render() = 0;
    
    // ゲームシーンコントローラーにシーンの切り替えを要請
    void requestSceneChange(SceneType type);
};

#endif /* GAMESCENE_H */