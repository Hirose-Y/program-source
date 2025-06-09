#ifndef GAMESCENE_OVER_H
#define GAMESCENE_OVER_H

#include <string>
#include <iostream>
#include "Scene/GameScene.h"
#include "InputActions/Context/InputContext_Over.h"

class Window;
class Shader;
class Image;


class GameOverScene : public GameScene
{
public:
    GameOverScene(GameSceneController* controller_, Window* window_);
    ~GameOverScene();

    void Enter() override;   // 入口処理
    void Exit() override;    // 出口処理

    void HandleInput() override;
    void Update(float deltaTime) override;
    void Render() override;

private:
    Window* window;

    std::unique_ptr<Shader> shader;
    std::unique_ptr<Image> toTilteimage;
    std::unique_ptr<Image> gameoverImage;
};

#endif /* GAMESCENE_OVER_H */