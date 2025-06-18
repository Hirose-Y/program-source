#ifndef STAGE_H
#define STAGE_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "Camera/Camera.h"
#include "Camera/CameraVariables.h"

#include "Core/Window.h"
#include "Graphics/Shader.h"
#include "Graphics/Image.h"
#include "Graphics/TextRenderer.h"

#include "Object/Object.h"
#include "Object/Object_Cube.h"
#include "Object/Object_Floor.h"
#include "Object/Object_Pyramid.h"
#include "Object/Object_Player.h"

#include "Input/InputSystem.h"

class Shader;
class World;
class Camera;
class Light;
class Window;
class PlayInputActions;

class Stage
{
public:
    Stage(Window* window_);
    ~Stage();

    void SetStage(const std::string& floorPath, const std::string& stickPath, const std::string& pyramidPath);
    
    void HandleInput(PlayInputActions* actions);
    void Update(float deltaTime);
    void Render();
    void Clear();

    bool isClear() const { return player->GetItemCounter() == pyramids.size(); }
    bool isGameOver() const { return player->isDead(); }
private:
    void Attachment();

    Window* window;

    std::unique_ptr<World> world;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Light> light;
    std::unique_ptr<Player> player;

    std::vector<std::unique_ptr<Floor>> floors;
    std::vector<std::unique_ptr<Cube>> cubes;
    std::vector<std::unique_ptr<Pyramid>> pyramids;

    std::unique_ptr<Shader> shader;
    std::unique_ptr<Shader> shader2D;
    std::unique_ptr<Shader> shaderText;

    std::unique_ptr<TextRenderer> text;
    std::unique_ptr<Image> UIimage_Pyramid;
};

#endif /* STAGE_H */