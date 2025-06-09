#ifndef GAMESCENE_TITLE_H
#define GAMESCENE_TITLE_H

#include <string>
#include <iostream>
#include "Scene/GameScene.h"
#include "InputActions/Context/InputContext_Title.h"

class Window;
class Shader;
class Image;

class TitleScene : public GameScene
{
public:
    TitleScene(GameSceneController* controller_, Window* window_);
    ~TitleScene();

    void Enter() override;   // 入口処理
    void Exit() override;    // 出口処理

    void HandleInput() override;
    void Update(float deltaTime) override;
    void Render() override;

private:
    Window* window;

    std::unique_ptr<Shader> shader;
    std::unique_ptr<Image> image;
    std::unique_ptr<Image> titleImage;
};

#endif /* GAMESCENE_TITLE_H */