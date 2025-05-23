#ifndef _GAME_H_
#define _GAME_H_

#include <memory>

class Window;
class GameSceneController;

class Game
{
public:
    Game();
    ~Game();

    // ゲームを初期化する
    bool Initialize();
    // ゲームオーバーまでゲームループを実行する
    void RunLoop();
    // ゲームをシャットダウンする
    void Shutdown();

private:
    // ゲームループのためのヘルパー関数群
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    bool mIsRunning;
    float lastFrameTime;
    float deltaTime;

    std::unique_ptr<Window> window;

    std::unique_ptr<GameSceneController> controller;
};

#endif /* _GAME_H_ */