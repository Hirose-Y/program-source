#include "World/WorldRotator.h"
#include "World/World.h"
#include "Camera/Camera.h"

#include "Core/GLHeaders.h"
#include "Utils/Helper.h"

#include <iostream>

WorldRotator::WorldRotator(World* world_)
:world(world_), state(State::Idle), axis(glm::vec3(0.0f, 0.0f, 1.0f)), progress(0.0f), targetAngle(0.0f), baseaxis(glm::vec3(0, 0, 1))
{
    currentGravityDir = glm::vec3(0.0f, -1.0f, 0.0f);
    previoursGravityDir = glm::vec3(0.0f, -1.0f, 0.0f);
    rotCounter = 4;
    gravityIndex = rotCounter % 4;
}

WorldRotator::~WorldRotator()
{

}

void WorldRotator::StartRotation(int direction, glm::vec3 axis_, float target_, float speed_)
{
    rotCounter += direction;
    if(rotCounter == 8) rotCounter = 4;
    if(rotCounter == 0) rotCounter = 4;

    gravityIndex = rotCounter % 4;
    axis = axis_;
    targetAngle = glm::radians(target_);
    rotationSpeed = glm::radians(speed_);
    
    // 回転開始
    state = State::Start;
}

void WorldRotator::Reset()
{
    state = State::Idle;
    progress = 0.0f;
    targetAngle = 0.0f;
}

void WorldRotator::Update(float deltaTime, glm::mat4& worldMatrix)
{
    float deltaAngle;
    glm::mat4 rot;

    switch (state)
    {
    case State::Idle:
        //Helper::printVec3("WorldRotator", "currFront", world->GetCamera()->getCurrentCameraFront());
        break;
    case State::Start:
        world->ExecuteCallback("RotateStartCallback_Camera");
        state = State::Rotating;
        break;
    case State::Rotating:
        deltaAngle = rotationSpeed * deltaTime;

        if (progress + deltaAngle >= targetAngle) 
        {
            deltaAngle = targetAngle - progress;
            state = State::Finish;
        }

        rot = glm::rotate(glm::mat4(1.0f), deltaAngle, axis);
        worldMatrix = rot * worldMatrix;
        progress += deltaAngle;
        break;
    case State::Finish:
        CalcGravityDir();
        world->RotateGravity();
        Reset();
        break;
    
    default:
        break;
    }
}

void WorldRotator::CalcGravityDir()
{    
    previoursGravityDir = currentGravityDir;
    currentGravityDir = Helper::KeepMaxComponent(glm::vec3(world->GetWorldRotation() * glm::vec4(glm::vec3(0, -1, 0), 0)));
    Helper::printVec3("rotator", "gravity", currentGravityDir);
}