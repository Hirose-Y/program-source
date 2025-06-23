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

}

WorldActions::~WorldActions()
{

}

bool WorldActions::ShouldStartRotationWorld(WorldRotator& rotator) const
{
    auto& keyboard = input.GetKeyboard();
    auto& pad = input.GetGamePad();

    const Camera* camera = rotator.GetWorld()->GetCamera();

    float angle = Helper::GetSignedAngleBetweenVectors(
        rotator.getBaseAxis(), camera->getCurrentPlayerFront(), -rotator.GetCurrentGravityDir()
    );
   
    //std::cout << "ANGLE: " << angle << std::endl;
    
    if (keyboard.IsKeyPressedOnce(GLFW_KEY_Q) || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_LEFT_BUMPER))
    {
        glm::vec3 axis = DesideRotationAxis(angle, true, &rotator);
        Helper::printVec3("WORLDACTION_L", "axis", axis);
        rotator.StartRotation(axis, -90.0f, -180.0f);
        return true;
    }

    if (keyboard.IsKeyPressedOnce(GLFW_KEY_E) || pad.IsButtonPressedOnce(GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER))
    {
        glm::vec3 axis = DesideRotationAxis(angle, false, &rotator);
        Helper::printVec3("WORLDACTION_R", "axis", axis);
        rotator.StartRotation(axis, 90.0f, 180.0f);
        return true;
    }

    return false;
}

glm::vec3 WorldActions::DesideRotationAxis(float angle, bool pressLQ, WorldRotator* rotator) const
{
    glm::vec3 axis;

    float absAngle = abs(angle);
    bool parallel = (absAngle >= 0 && absAngle <= 30) || (absAngle >= 150 && absAngle <= 180);
    bool diagonal = (absAngle > 30 && absAngle <= 60) || (absAngle > 120 && absAngle < 150);
    bool minus = (angle < 0.0f);

    // 前回の回転軸とカメラの向きがほとんど平行のとき、回転軸はプレイヤ－の後方
    if(parallel)
    {
        axis = rotator->getBaseAxis() * -rotator->GetWorld()->GetCamera()->getCurrentPlayerFront();
    }
    // 前回の回転軸に対してカメラの向きが斜めのとき、LR,QEによって回転軸を決定する
    else if (diagonal)
    {
        if(pressLQ)
        {
            axis *= -1.0f;
            
            axis = Helper::NormalizeOrZero(Helper::KeepMaxComponent(axis));
            if(minus) { axis = -axis; }       
        }else{
            axis = glm::cross(rotator->GetCurrentGravityDir(), axis);

            axis = Helper::NormalizeOrZero(Helper::KeepMaxComponent(axis));
            if(minus) { axis = -axis; }
        }
    }
    // 前回の回転軸とカメラの向きがほとんど直角の時、回転軸と重力のクロス積により新しい回転軸を決定
    else
    {
        axis = glm::cross(rotator->GetCurrentGravityDir(), rotator->getBaseAxis());

        axis = Helper::NormalizeOrZero(Helper::KeepMaxComponent(axis));
        if(minus) { axis = -axis; }
    }

    rotator->setBase(axis);

    return axis;
}