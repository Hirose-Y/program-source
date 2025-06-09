#include "Stage/Stage.h"
#include "Stage/StageBuilder.h"

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>

#include "Core/GLHeaders.h"
#include "Camera/Camera.h"
#include "Camera/CameraVariables.h"

#include "Core/Window.h"
#include "Graphics/Shader.h"
#include "Graphics/Image.h"
#include "World/World.h"
#include "Graphics/Light.h"

#include "Object/Object.h"
#include "Object/ObjectInfo.h"
#include "Object/Object_Cube.h"
#include "Object/Object_Floor.h"
#include "Object/Object_Pyramid.h"

#include "InputActions/Context/InputContext_Play.h"

Stage::Stage(Window* window_)
: window(window_)
{
    //Shaderプログラムを作成する
    shader = std::make_unique<Shader>("Shaders/vertex.vert", "Shaders/fragment.frag");
    shader2D = std::make_unique<Shader>("Shaders/vert2D.vert", "Shaders/frag2D.frag");
    shaderText = std::make_unique<Shader>("Shaders/text.vert", "Shaders/text.frag");

    // テキストやUIの準備
    text = std::make_unique<TextRenderer>();
    UIimage_Pyramid = std::make_unique<Image>("Assets/image/pyramid.png");

    text->LoadFont("Assets/fonts/Mplus1-Regular.ttf", 48);
    // ウィンドウサイズの変化にも対応
    text->SetProjection(glm::ortho(0.0f, window->GetWidth(), 0.0f, window->GetHeight()));


    world = std::make_unique<World>();

    CameraTransform initCameraTrans = { glm::vec3(0.0f, 2.0f, 4.0f),    //カメラの位置
                                        glm::vec3(0.0f, 0.0f, 0.0f),    //カメラの向き（原点)
                                        glm::vec3(0.0f, 1.0f, 0.0f) };    //カメラの上方向

    CameraProjection initCameraProjection = { 45.0f,  //fov
                                              window->GetWidth() / window->GetHeight(),    //アスペクト比
                                              0.1f,
                                              100.0f }; // 透視投影
    
    camera = std::make_unique<Camera>(initCameraTrans, initCameraProjection, world.get());
    window->SetCamera(camera.get());
    world->SetCamera(camera.get());
    light = std::make_unique<Light>();
    light->position = glm::vec3(0.0f, 10.0f, 0.0f);
    light->lightDir = glm::vec3(0.0f, 0.0f, 0.0f);
    light->lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    player = std::make_unique<Player>(1, shader.get(), glm::vec3(0.0f, 1.0f, 0.0f), world.get(), camera.get());

    camera->SetTarget(player.get());

}

Stage::~Stage()
{
    shader->remove();
}

void Stage::SetStage(const std::string& floorPath, const std::string& stickPath, const std::string& pyramidPath)
{
    StageBuilder builder(shader.get(), world.get());
    builder.LoadFloors(floorPath, floors);
    builder.LoadSticks(stickPath, cubes);
    builder.LoadPyramids(pyramidPath, pyramids);

    //ステージの各オブジェクトをプレイヤーにアタッチ
    Attachment();

    #ifdef DEBUG_MODE
    std::cout << "[Class::Stage] Genarate Stage" << std::endl;
    #endif
}

void Stage::Attachment()
{
    //各コリダーをプレイヤーにアタッチ
    for(auto& cube : cubes) { player->AttachmentStage(cube.get()); }
    for(auto& floor :floors) { player->AttachmentStage(floor.get()); }
    for(auto& pyramid :pyramids) { player->AttachmentStage(pyramid.get()); }
}

void Stage::HandleInput(const PlayInputActions* actions)
{
    world->ProcessInput(actions);
    player->ProcessInput(actions);
    camera->ProcessInput(actions);
}

void Stage::Update(float deltaTime)
{
    for (auto& floor : floors) { floor->Update(deltaTime); }
    for (auto& cube : cubes)   { cube->Update(deltaTime); }
    for (auto& pyramid : pyramids)   { pyramid->Update(deltaTime); }

    world->Update(deltaTime);
    player->Update(deltaTime);
    camera->Update(deltaTime);
}

void Stage::Render()
{
    glClearColor(0.3f, 0.2f, 0.8f, 0.0f);

    shader->use();

    std::vector<Object*> opaqueObjects;
    std::vector<Object*> transparentObjects;

    auto collect = [&](auto& container)
    {
        for(auto& obj : container) {
            if(obj->IsTransparent())
            {
                transparentObjects.push_back(obj.get());
            }else{
                opaqueObjects.push_back(obj.get());
            }
        }
    };

    collect(floors);
    collect(cubes);
    collect(pyramids);

    for(auto obj : opaqueObjects)
    {
        obj->draw(camera.get(), light.get());
    }

    player->draw(camera.get(), light.get());

    for(auto obj : transparentObjects)
    {
        obj->draw(camera.get(), light.get());
    }

    glDisable(GL_DEPTH_TEST);
    //UIの描画（ピラミッドの画像）
    shader2D->use();
    glm::vec2 position = glm::vec2(40, 70);
    glm::vec2 scale = glm::vec2(30, 35);
    UIimage_Pyramid->draw(shader2D.get(), position, scale);

    //UIの描画（ピラミッドを取得した数）
    shaderText->use();
    std::string pyramidCounter = std::to_string(player->GetItemCounter());
    std::string pyramidMax = std::to_string(pyramids.size());
    std::string pyramidUI = pyramidCounter + ' ' + "/" + ' ' + pyramidMax;
    text->RenderText(pyramidUI, 80.0f, 50.0f, 1.0f, shaderText.get());

    //UIの描画（残り回転可能回数）
    std::string worldRotateCounter = std::to_string(world->GetRotLimit());
    std::string RotateionUI = "RotationLimit : " + worldRotateCounter;
    text->RenderText(RotateionUI, 330.0f, 30.0f, 1.0f, shaderText.get());
    glEnable(GL_DEPTH_TEST);
}

void Stage::Clear()
{
    player->ClearStage();
    floors.clear();
    cubes.clear();
    pyramids.clear();
}