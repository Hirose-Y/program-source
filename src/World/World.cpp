#include "World/World.h"
#include "World/WorldRotator.h"

#include "Core/GLHeaders.h"
#include "Input/InputSystem.h"
#include "InputActions/Context/InputContext_Play.h"
#include <iostream>
#include <vector>
#include <functional>

#include "Camera/Camera.h"

#include "Utils/Helper.h"

World::World()
:rotator(this)
{
    rotLimit = 3;
    worldMatrix = glm::mat4(1.0f);
    gravityDirection = glm::vec3(0.0f, -1.0f, 0.0f);
    size = glm::vec3(50.0f, 50.0f, 50.0f);
    gravity = 20;

    Helper::printMatrix("World", "World Matrix", worldMatrix);
}

World::~World()
{
    callbackFunctions.Clear();
}

void World::SetCamera(Camera* camera_)
{
    camera = camera_;
}

void World::Initialize(glm::vec3 pos, glm::vec3 sc)
{
    
}

void World::ProcessInput(PlayInputActions* input)
{
    if(rotLimit == 0 || rotator.IsRotating()) { return; }

    if (input->world.ShouldStartRotationWorld(rotator)) {
        prevWorldMatrix = worldMatrix;
        rotLimit--;
    }
}

void World::Update(float deltaTime)
{
    rotator.Update(deltaTime, worldMatrix);
}

void World::RotateGravity()
{
    gravityDirection = rotator.GetCurrentGravityDir();
    Helper::AjastMatrix(worldMatrix);
    Helper::printMatrix("World", "World Matrix", worldMatrix);
    //回転終了後のコールバック
    ExecuteCallback("OnRotateFinishCallback_Player");
    ExecuteCallback("RotateFinishCallback_Camera");
}

// playerの「OnFloor() == true」のときに呼ばれる
void World::RotateReset()
{
    rotLimit = 3;
}

void World::ExecuteCallback(const std::string& name)
{
    callbackFunctions.Execute(name);
}