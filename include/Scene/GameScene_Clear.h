#ifndef GAMESCENE_CLEAR_H
#define GAMESCENE_CLEAR_H

#include <string>
#include <iostream>
#include "Scene/GameScene.h"
#include "Scene/GameSceneController.h"
#include "InputActions/Context/InputContext_Clear.h"

class Window;
class Shader;
class Image;

class ClearScene : public GameScene 
{
public:
    ClearScene(GameSceneController* controller_, Window* window_);
    ~ClearScene();
    
    void Enter() override;   // 入口処理
    void Exit() override;    // 出口処理

    void HandleInput() override;
    void Update(float deltaTime) override;
    void Render() override;

private:
    Window* window;

    std::unique_ptr<Shader> shader;
    std::unique_ptr<Image> toTilteimage;
    std::unique_ptr<Image> gameclearImage;
};


#endif /* GAMESCENE_CLEAR_H */