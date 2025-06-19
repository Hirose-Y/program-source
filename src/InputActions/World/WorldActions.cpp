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

    float angle = Helper::GetSignedAngleBetweenVectors(rotator.getBaseAxis(), camera->getCurrentPlayerFront(), -rotator.GetCurrentGravityDir());
    // Helper::printVec3("BASE", "camerafront", camera->getCurrentCameraFront());
    // std::cout << "ANGLE: " << angle << std::endl;

    // // DesideRotationAxis(angle, true, &rotator);
    //   Helper::printVec3("BASE", "baseaxis", rotator.getBaseAxis());

    if (keyboard.IsKeyPressedOnce(GLFW_KEY_Q) || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_LEFT_BUMPER))
    {   
         DesideRotationAxis(angle, true, &rotator);
        // Helper::printVec3("WorldActions", "camForward", camForward);
        // Helper::printVec3("WORLDACTION_L", "axis", rotationAxis);
         rotator.StartRotation(-1, -rotationAxis, 90.0f, 180.0f);
        //rotator.StartRotation(1, glm::vec3(0, 0, 1), 90.0f, 180.0f); // 左回転
        return true;
    }

    if (keyboard.IsKeyPressedOnce(GLFW_KEY_E) || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER))
    {
         DesideRotationAxis(angle, false, &rotator);
        // Helper::printVec3("WorldActions", "camForward", camForward);
        // Helper::printVec3("WORLDACTION_R", "axis", rotationAxis);
         rotator.StartRotation(1, rotationAxis, 90.0f, 180.0f);
        //rotator.StartRotation(-1, -glm::vec3(0, 0, 1), 90.0f, 180.0f); // 左回転
        return true;
    }

    return false;
}

void WorldActions::DesideRotationAxis(float angle, bool pressLQ, WorldRotator* rotator) const
{
    glm::vec3 axis;

    float absAngle = abs(angle);
    bool parallel = (absAngle >= 0 && absAngle <= 30) || (absAngle >= 150 && absAngle <= 180);
    bool diagonal = (absAngle > 30 && absAngle <= 60) || (absAngle > 120 && absAngle < 150);
    bool minus = (angle < 0.0f);

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
        if(pressLQ)
        {
            axis = -rotationAxis;       
            Helper::printVec3("", "", axis);
        }else{
            axis = glm::cross(rotator->GetCurrentGravityDir(), rotationAxis);

        }
    }
    // 前回の回転軸とカメラの向きがほとんど直角の時、回転軸と重力のクロス積により新しい回転軸を決定
    else
    {
        Helper::printStr("", "right angle");
        Helper::printVec3("GRAVITY", "", rotator->GetCurrentGravityDir());
        Helper::printVec3("BASESE", "", rotator->getBaseAxis());
        axis = glm::cross(rotator->GetCurrentGravityDir(), rotator->getBaseAxis());
    }

    // 回転軸を更新
    axis = Helper::NormalizeOrZero(Helper::KeepMaxComponent(axis));
    if(minus)
    {
        axis = -axis;
    }
    rotationAxis = axis;
    rotator->setBase(rotationAxis);
}