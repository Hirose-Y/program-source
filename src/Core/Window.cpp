#include <iostream>
#include "Core/GLHeaders.h"

#include "Camera/Camera.h"
#include "Core/Window.h"
#include "Input/InputSystem.h"

Window::Window(int width, int height, const char *title)
    : window(glfwCreateWindow(width, height, title, nullptr, nullptr))
    , scale(100.0f), input(), camera(nullptr)
{
    if (window == nullptr)
    {
        // ウィンドウが作成できなかった
        std::cerr << "Can't create GLFW window." << std::endl;
        exit(1);
    }

    // 現在のウィンドウを処理対象にする
    glfwMakeContextCurrent(window);

    // GLAD を初期化する
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // GLAD の初期化に失敗した
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }
    glEnable(GL_DEPTH_TEST); // 奥行きを有効化
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, width, height);    //描画領域の設定
    glfwSwapInterval(1);    // 垂直同期のタイミングを待つ

    // 各コールバック関数の登録
    glfwSetWindowSizeCallback(window, resize);  // ウィンドウのサイズ変更時
    glfwSetScrollCallback(window, wheel);       // マウスホイール操作時
    glfwSetKeyCallback(window, keyboardEvent);  // キーボード操作時

    // このインスタンスの this ポインタを記録しておく
    glfwSetWindowUserPointer(window, this);

    // 開いたウィンドウの初期設定
    resize(window, width, height);

    // 画面のクリア
    glClearColor(0.3f, 0.2f, 0.8f, 0.0f);
}


Window::~Window()
{
    glfwDestroyWindow(window);
}

Window::operator bool()
{
    glfwPollEvents();

    // ウィンドウを閉じる必要が無ければ true を返す
    return !glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE);
}

void Window::swapBuffers()
{
    // カラーバッファを入れ替える
    glfwSwapBuffers(window);
}

void Window::resize(GLFWwindow *const window, int width, int height)
{
    // フレームバッファのサイズを調べる
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

    // フレームバッファ全体をビューポートに設定する
    glViewport(0, 0, fbWidth, fbHeight);

    // このインスタンスの this ポインタを得る
    Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

    if (instance != NULL)
    {
        // 開いたウィンドウのサイズを保存する
        instance->width = static_cast<GLfloat>(width);
        instance->height = static_cast<GLfloat>(height);

        // カメラのアスペクト比を更新する
        if (instance->camera)
        {
            float aspect = (float)fbWidth / (float)fbHeight;
            instance->camera->SetAspectRatio(aspect);
        }
    }
}

void Window::wheel(GLFWwindow *window, double x, double y)
{
    // このインスタンスの this ポインタを得る
    Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

    if (instance != NULL)
    {
        // ワールド座標系に対するデバイス座標系の拡大率を更新する
        instance->scale += static_cast<GLfloat>(y);
    }
}

void Window::keyboardEvent(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // このインスタンスの this ポインタを得る
    Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

    if (instance != nullptr)
    {
        // キーの状態を保存する
        instance->input.OnKeyEvent(key, action);
    }

    #ifdef DEBUG_MODE
    std::cout << "[Class::Window] statsu: " << action << std::endl;
    #endif
}

void Window::LastUpdate()
{
    input.Update();
}

void Window::SetCamera(Camera* camera_)
{
    camera = camera_;
}