#ifndef GAMESCENE_PLAY_H
#define GAMESCENE_PLAY_H

#include <string>
#include <memory>
#include "Scene/GameScene.h"
#include "InputActions/Context/InputContext_Play.h"

class Window;
class Stage;
class PlayInputActions;
class Shader;
class Image;

class PlayScene : public GameScene 
{
public:
    PlayScene(GameSceneController* controller_, Window* window_);
    ~PlayScene();
    
    void Enter() override;   // 入口処理
    void Exit() override;    // 出口処理

    void HandleInput() override;
    void Update(float deltaTime) override;
    void Render() override;

private:
    void Initialize();

    Window* window;

    bool pause;
    int pauseMode;

    std::unique_ptr<Shader> shader2D;
    std::unique_ptr<Image> UIInfo_Pad;
    std::unique_ptr<Image> UIInfo_Key;

    std::unique_ptr<Stage> stage;

    std::unique_ptr<PlayInputActions> action;
};


#endif /* GAMESCENE_PLAY_H */