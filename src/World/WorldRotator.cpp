#include "World/WorldRotator.h"
#include "World/World.h"
#include "Camera/Camera.h"

#include "Core/GLHeaders.h"
#include "Utils/Helper.h"

#include <iostream>

WorldRotator::WorldRotator(World* world_)
:world(world_), state(State::Idle), rotaxis(glm::vec3(0.0f, 0.0f, 1.0f)), baseaxis(glm::vec3(0, 0, 1))
{
    currentGravityDir = glm::vec3(0.0f, -1.0f, 0.0f);
    rotCounter = 4;

    rot = glm::quat(1, 0, 0, 0);

    progress = 0.0f;
    targetAngle = 0.0f;
}

WorldRotator::~WorldRotator()
{

}

void WorldRotator::StartRotation(glm::vec3 axis_, float target_, float speed_)
{
    rotCounter--;
    if(rotCounter == 0) rotCounter = 4;

    rotaxis = axis_;
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

void WorldRotator::Update(float deltaTime, glm::quat& worldOrientation)
{
    float deltaAngle;
    glm::quat deltaRot = glm::quat(1, 0, 0, 0);

    switch (state)
    {
    case State::Idle:
        break;
    case State::Start:
        world->ExecuteCallback("RotateStartCallback_Camera");
        state = State::Rotating;
        break;
    case State::Rotating:
        deltaAngle = rotationSpeed * deltaTime;

        if ((targetAngle >= 0.0f && progress + deltaAngle >= targetAngle) ||
            (targetAngle < 0.0f && progress + deltaAngle <= targetAngle))
        {
            deltaAngle = targetAngle - progress;
            state = State::Finish;
        }

        deltaRot = glm::angleAxis(deltaAngle, rotaxis);
        worldOrientation = deltaRot * worldOrientation;

        progress += deltaAngle;
        break;
    case State::Finish:
        Helper::printVec3("ROTATOR", "BASE", baseaxis);
        CalcGravityDir();
        //回転終了後のコールバック
        world->ExecuteCallback("OnRotateFinishCallback_Player");
        world->ExecuteCallback("RotateFinishCallback_Camera");
        Reset();
        break;
    
    default:
        break;
    }
}

void WorldRotator::CalcGravityDir()
{    
    currentGravityDir = Helper::KeepMaxComponent(glm::vec3(world->GetWorldRotation() * glm::vec4(glm::vec3(0, -1, 0), 0)));
    Helper::printVec3("rotator", "gravity", currentGravityDir);
}