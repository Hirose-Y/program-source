#include "Camera/Camera.h"
#include "Object/Object_Player.h"
#include "World/World.h"

#include "Input/InputSystem.h"
#include "InputActions/Context/InputContext_Play.h"
#include <iostream>

#include "Utils/Helper.h"

Camera::Camera(CameraTransform trans, CameraProjection proj, World* world_)
: currentTransform(trans), projection(proj), target(nullptr), world(world_)
{
    distance = 4.0f;
    offsetBase = glm::vec3(0, 1, distance);
    orientation = glm::quat(1, 0, 0, 0);    //単位クォータニオン
    yawInput = 0.0f;
    pitchInput = 0.0f;

    provisonalTransform = currentTransform;
    Initialize(currentTransform, projection);

    world->AddCallback(
        "RotateStartCallback_Camera",
        
        [this]() 
        {
            Helper::printStr("Camera", "-----------Camera Rotation Start--------");

            provisonalTransform = currentTransform;
        });

    world->AddCallback(
        "RotateFinishCallback_Camera", 
        
        [this]()
        {
            provisonalTransform.direction = currentTransform.direction;
            provisonalTransform.up = Helper::KeepMaxComponent(currentTransform.up);

            RollAroundViewAxis(90.0f);
            
            // rotation.yawAxis = glm::vec3(world->GetWorldRotation() * glm::vec4(glm::vec3(0, 1, 0), 0));
            // rotation.pitchAxis = glm::vec3(world->GetWorldRotation() * glm::vec4(glm::vec3(1, 0, 0), 0));
            
            Helper::printVec3("Camera", "offset", offsetBase);
            Helper::printVec3("Camera", "front", getCurrentCameraFront());
            Helper::printStr("", "----------ROTATE FINISH----------");
        });
}

Camera::~Camera()
{

}

void Camera::Initialize(CameraTransform trans, CameraProjection proj)
{
    viewMatrix = glm::lookAt(
        trans.position,
        trans.direction,
        trans.up
    );

    projectionMatrix = glm::perspective(
        glm::radians(proj.fov),
        proj.aspectRatio,
        proj.nearPlane,
        proj.farPlane
    );
}

void Camera::ProcessInput(PlayInputActions* input)
{
    yawInput = 0.0f;
    pitchInput = 0.0f;
    input->camera.ShouldRotationYaw(yawInput);
    input->camera.ShouldRotationPitch(pitchInput);

    int roll = 0;

    if (input->camera.ShouldRoll() == 1) {
        RollAroundViewAxis(-0.05f); // 左に傾ける
    }
    if (input->camera.ShouldRoll() == 2) {
        RollAroundViewAxis(0.05f); // 右に傾ける
    }

    if(input->camera.ResetYawAndPitch())
    {
        orientation = glm::quat(1, 0, 0, 0);
    }
}

void Camera::Update(float deltaTime)
{
    if (!target) return;

    // --- ロール補間処理 ---
    if (isRolling) {
        rollTimer += deltaTime;
        float t = glm::clamp(rollTimer / rollDuration, 0.0f, 1.0f);
        float currentAngle = glm::mix(rollStartAngle, rollTargetAngle, t);

        glm::quat qRoll = glm::angleAxis(glm::radians(currentAngle), currentTransform.direction);
        orientation = qRoll * orientation;

        if (t >= 1.0f) {
            isRolling = false;
        }
    }

    glm::vec3 up = -world->GetCurrentGravityDir();
    glm::vec3 right = glm::normalize(glm::cross(up, orientation * glm::vec3(0, 0, -1)));

    glm::quat qYaw = glm::angleAxis(glm::radians(yawInput * 90.0f * deltaTime), up);
    glm::quat qPitch = glm::angleAxis(glm::radians(pitchInput * 30.0f * deltaTime), right);

    orientation = qYaw * qPitch * orientation;

    glm::vec3 offset = orientation * offsetBase;
    currentTransform.position = target->getPosition() + offset;
    currentTransform.direction = glm::normalize(target->getPosition() - currentTransform.position);
    currentTransform.up = orientation * glm::vec3(0, 1, 0);

    updateViewMatrix();
}

void Camera::SetTarget(Player* player)
{
    target = player;
}

void Camera::SetPosition(glm::vec3 pos)
{
    currentTransform.position = pos;
    updateViewMatrix();
}

void Camera::SetAspectRatio(float aspect)
{
    projection.aspectRatio = aspect;
    updateProjectionMatrix();
}

void Camera::updateViewMatrix()
{
    if (target)
    {
        viewMatrix = glm::lookAt(
            currentTransform.position,
            target->getPosition() + currentTransform.direction,
            currentTransform.up
        );
    }
    else
    {
        viewMatrix = glm::lookAt(
            currentTransform.position,
            currentTransform.position + currentTransform.direction,
            currentTransform.up
        );
    }
}

void Camera::updateProjectionMatrix()
{
    projectionMatrix = glm::perspective(
        glm::radians(projection.fov),
        projection.aspectRatio,
        projection.nearPlane,
        projection.farPlane
    );
}

const glm::vec3 Camera::getProvCameraFront() const
{
    glm::vec3 gravity = world->GetCurrentGravityDir();
    glm::vec3 dir = provisonalTransform.direction;

    // dirベクトルから重力成分を取り除いて水平成分だけ取り出す
    glm::vec3 flatForward = dir - glm::dot(dir, gravity) * gravity;

    // 長さが0に近いときはfallbackする
    if (glm::length(flatForward) < 0.001f)
    {
        // fallback: worldのZ軸を使う
        return glm::normalize(glm::cross(gravity, glm::vec3(1, 0, 0)));
    }

    return glm::normalize(flatForward);
}

const glm::vec3 Camera::getCurrentCameraFront() const 
{
    glm::vec3 gravity = world->GetCurrentGravityDir();
    glm::vec3 dir = currentTransform.direction;

    // dirベクトルから重力成分を取り除いて水平成分だけ取り出す
    glm::vec3 flatForward = glm::normalize( dir - glm::dot(dir, gravity) * gravity );

    // 長さが0に近いときはfallbackする
    if (glm::length(flatForward) < 0.001f)
    {
        // fallback: worldのZ軸を使う
        return glm::normalize(glm::cross(gravity, glm::vec3(1, 0, 0)));
    }

    // Helper::printVec3("Camera", "CurrCamFront", Helper::NormalizeOrZero(flatForward));

    return Helper::RoundToZero(flatForward);
}

const glm::vec3 Camera::getCurrentCameraRight() const
{
    glm::vec3 upAxis = -world->GetCurrentGravityDir();
    glm::vec3 flatForward = getCurrentCameraFront();
    glm::vec3 right = glm::normalize(glm::cross(flatForward, upAxis));

    return right;
}

void Camera::RollAroundViewAxis(float angleDegrees)
{
    glm::vec3 axis = getCurrentCameraFront();
    glm::quat qRoll = glm::angleAxis(glm::radians(angleDegrees), axis);
    orientation = qRoll * orientation;
}

void Camera::StartRoll(float angleDeg, float durationSec)
{
    isRolling = true;
    rollTimer = 0.0f;
    rollDuration = durationSec;
    rollStartAngle = 0.0f;
    rollTargetAngle = angleDeg;
}