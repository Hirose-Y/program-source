#include "World/WorldRotator.h"
#include "World/World.h"
#include "Camera/Camera.h"

#include "GLHeaders.h"
#include "Utils/Helper.h"

#include <iostream>

WorldRotator::WorldRotator(World* world_)
:world(world_), state(State::Idle), axis(glm::vec3(0.0f, 0.0f, 1.0f)), progress(0.0f), targetAngle(0.0f)
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
        break;
    case State::Start:
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
        world->RotateCamera();
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
    const Camera* camera = world->GetCamera();
    glm::vec3 camForward = camera->getCurrentCameraFront();

    previoursGravityDir = currentGravityDir;
    Helper::printVec3("WorldR", "prG", previoursGravityDir);
    
    currentGravityDir = -glm::normalize(camera->getUPDirection());
    currentGravityDir = Helper::RoundToZero(currentGravityDir);
    currentGravityDir = glm::normalize(Helper::KeepMaxComponent(currentGravityDir));

    glm::vec3 forward = Helper::KeepMaxComponent(
        glm::normalize(camForward - glm::dot(camForward, currentGravityDir) * currentGravityDir)
    );

    Helper::printVec3("WorldActions", "prevGravyDir", previoursGravityDir);
    Helper::printVec3("WorldActions", "gravityDir", currentGravityDir);
    Helper::printVec3("WorldActions", "camForward", camForward);
    Helper::printVec3("WorldActions", "forward", forward);

    // 正しい回転軸を決定（forward と gravity の外積）
    glm::vec3 cameraleft = glm::cross(camForward, currentGravityDir);

    // 万が一、カメラが重力方向と平行なら適当な軸を使用
    if (glm::length(cameraleft) < 0.01f) {
        cameraleft = glm::vec3(0, 0, 1); // fallback
    }
    cameraleft = glm::normalize(cameraleft);

    Helper::printVec3("WorldRotator", "rotateAxis", cameraleft);
}