#include "Input/InputSystem.h"
#include "InputActions/World/WorlsActions.h"
#include "Core/GLHeaders.h"
#include "Scene/SceneType.h"

#include "World/World.h"
#include "World/WorldRotator.h"
#include <iostream>

#include "Camera/Camera.h"
#include "Utils/Helper.h"

WorldActions::WorldActions(InputSystem& input_)
:input(input_)
{
    rotationAxis = glm::vec3(0, 0, 1);
    baseAxis = glm::vec3(0, 0, 1);
}

WorldActions::~WorldActions()
{

}

bool WorldActions::ShouldStartRotationWorld(WorldRotator& rotator) const
{
    auto& keyboard = input.GetKeyboard();
    auto& pad = input.GetGamePad();

    const Camera* camera = rotator.GetWorld()->GetCamera();
    glm::vec3 camForward = camera->getCurrentCameraFront();

    float angle = Helper::GetSignedAngleBetweenVectors(baseAxis, camera->getCurrentCameraFront(), camera->getUPDirection());
    // Helper::printVec3("BASE", "camerafront", camera->getCurrentCameraFront());
       std::cout << "ANGLE: " << angle << std::endl;

    // DesideRotationAxis(angle, true, &rotator);
     Helper::printVec3("BASE", "baseaxis", baseAxis);

    if (keyboard.IsKeyPressedOnce(GLFW_KEY_Q) || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_LEFT_BUMPER))
    {   
        DesideRotationAxis(angle, true, &rotator);
        Helper::printVec3("WorldActions", "camForward", camForward);
        Helper::printVec3("WORLDACTION_L", "axis", rotationAxis);
        rotator.StartRotation(-1, -rotationAxis, 90.0f, 180.0f);
        return true;
    }

    if (keyboard.IsKeyPressedOnce(GLFW_KEY_E) || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER))
    {
        DesideRotationAxis(angle, false, &rotator);
        Helper::printVec3("WorldActions", "camForward", camForward);
        Helper::printVec3("WORLDACTION_R", "axis", rotationAxis);
        rotator.StartRotation(1, rotationAxis, 90.0f, 180.0f);
        return true;
    }

    return false;
}

void WorldActions::DesideRotationAxis(float angle, bool pressLQ, WorldRotator* rotator) const
{
    glm::vec3 axis;

    float absAngle = abs(angle);
    bool parallel = (absAngle >= 0 && absAngle <= 30) || (absAngle >= 150 && absAngle <= 180);
    bool diagonal = (absAngle > 30 && absAngle <= 60) || (absAngle > 120 && absAngle <= 150);
    bool minus = false;

    // 前回の回転軸とカメラの向きがほとんど平行のとき、回転軸はそのまま 
    if(parallel)
    {
        Helper::printStr("", "parallel");
        minus = (absAngle >= 0 && absAngle <= 30);
        axis = rotationAxis;
    }
    // 前回の回転軸に対してカメラの向きが斜めのとき、LR,QEによって回転軸を決定する
    else if (diagonal)
    {
        Helper::printStr("", "diagonal");
        minus = (angle < 0.0f);
        if(pressLQ)
        {
            axis = -glm::cross(rotator->GetCurrentGravityDir(), rotationAxis);
            Helper::printVec3("", "", axis);
        }else{
            axis = -rotationAxis;    
        }
    }
    // 前回の回転軸とカメラの向きがほとんど直角の時、回転軸と重力のクロス積により新しい回転軸を決定
    else
    {
        minus = (angle < 0.0f);
        Helper::printStr("", "right angle");
        glm::vec3 front = Helper::NormalizeOrZero(rotator->GetWorld()->GetCamera()->getCameraFront());
        Helper::printVec3("GRAVITY", "", rotator->GetCurrentGravityDir());
        Helper::printVec3("BASESE", "", baseAxis);
        axis = glm::cross(rotator->GetCurrentGravityDir(), baseAxis);
    }

    // 回転軸を更新
    axis = Helper::NormalizeOrZero(Helper::KeepMaxComponent(axis));
    if(minus)
    {
        axis = -axis;
    }
    rotationAxis = axis;
    baseAxis = rotationAxis;
    Helper::printVec3("BASESE", "", baseAxis);
    rotator->setBase(baseAxis);
}