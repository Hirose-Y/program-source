#ifndef _GAME_H_
#define _GAME_H_

#include <string>
#include <memory>

class Window;
class AppContext;
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
    std::unique_ptr<AppContext> context;
    std::unique_ptr<GameSceneController> controller;
};

#endif /* _GAME_H_ */