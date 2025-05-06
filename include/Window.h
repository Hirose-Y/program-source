#ifndef WINDOW_H
#define WINDOW_H

#include "GLHeaders.h"
#include <memory>
#include <unordered_map>

#include "Input/Keyboard.h"
#include "Input/InputSystem.h"
class Camera;

// ウィンドウ関連の処理
class Window
{
public:
    Window(int width, int height, const char *title);
    virtual ~Window();

    // 描画ループの継続判定
    explicit operator bool();
    // ダブルバッファリング
    void swapBuffers();

    void SetCamera(Camera* camera_);

    // 毎フレームの最後に行う処理
    void LastUpdate();

    const GLfloat GetWidth() const { return width; }
    const GLfloat GetHeight() const { return height; }

    // ワールド座標系に対するデバイス座標系の拡大率を取り出す
    GLfloat getScale() const { return scale; }

    GLFWwindow* getWindow() const { return window; }

    // インプットシステムを得る
    InputSystem& GetInputSystem() { return input; }
private:
    // キーボード操作時の処理
    static void keyboardEvent(GLFWwindow *window, int key, int scancode, int action, int mods);
    // ウィンドウのサイズ変更時の処理
    static void resize(GLFWwindow *const window, int width, int height);
    // マウスホイール操作時の処理
    static void wheel(GLFWwindow *window, double x, double y);


    GLFWwindow* const window;   // ウィンドウのハンドル
    Camera* camera;

    InputSystem input;
    
    // ウィンドウのサイズ
    GLfloat width;
    GLfloat height;

    // ワールド座標系に対するデバイス座標系の拡大率
    GLfloat scale;
};

#endif /* WINDOW_H */