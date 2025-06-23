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
    orientation = glm::quat(1, 0, 0, 0);
    size = glm::vec3(50.0f, 50.0f, 50.0f);
    gravity = 20;

    Helper::printMatrix("World", "World Matrix", glm::mat4_cast(orientation));
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
        rotLimit--;
    }
}

void World::Update(float deltaTime)
{
    rotator.Update(deltaTime, orientation);
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