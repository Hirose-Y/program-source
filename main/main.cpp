#include "Core/GLHeaders.h"
#include <iostream>

#include "Core/Game.h"

int main(int argc, char** argv)
{
    // glfwを初期化する
    if (!glfwInit())
    {
        std::cerr << "Can't initialize GLFW." << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    auto game = Game();
    bool success = game.Initialize();
    if (success)
    {
        game.RunLoop();
    }

    game.Shutdown();
    glfwTerminate();
    
    return 0;
}
