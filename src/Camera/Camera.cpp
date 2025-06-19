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
    offsetBase = glm::vec3(0, 0, distance);
    orientation = glm::quat(1, 0, 0, 0);
    baseOrientation = glm::quat(1, 0, 0, 0);
    mRoll = glm::quat(1, 0, 0, 0);
    yawInput = 0.0f;
    pitchInput = 0.0f;

    Initialize(currentTransform, projection);

    world->AddCallback(
        "RotateStartCallback_Camera",
        
        [this]() 
        {
            Helper::printStr("Camera", "-----------Camera Rotation Start--------");
            Helper::printMatrix("Camera", "mat4world", world->GetWorldRotation());
            Helper::printMatrix("Camera", "mat4", glm::mat4_cast(orientation));
        });

    world->AddCallback(
        "RotateFinishCallback_Camera", 
        
        [this]()
        {
            // orientation = glm::quat_cast(world->GetWorldRotation()) * baseOrientation;
            glm::mat4 m = glm::mat4_cast(glm::quat_cast(world->GetWorldRotation()));

            Helper::printMatrix("Camera", "mat4world", m);
            Helper::printMatrix("Camera", "mat4", glm::mat4_cast(orientation));
            
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

    if(input->camera.ResetYawAndPitch())
    {
        orientation = glm::quat(1, 0, 0, 0) * glm::quat_cast(world->GetWorldRotation());
        Helper::printMatrix("Camera", "mat4", glm::mat4_cast(orientation));
    }
}

void Camera::Update(float deltaTime)
{
    if (!target) return;

    glm::vec3 up = -world->GetCurrentGravityDir();
    glm::vec3 right = glm::normalize(glm::cross(orientation * world->GetRotator().GetAxis(), up));

    qYaw = glm::angleAxis(glm::radians(yawInput * 90.0f * deltaTime), up);
    qPitch = glm::angleAxis(glm::radians(pitchInput * 30.0f * deltaTime), right);

    glm::quat qWorldRoll = glm::quat(1, 0, 0, 0);
    glm::vec3 offset = orientation * offsetBase;

    // --- ロール補間処理 ---
    if (world->isWorldRotation()) {
        // ワールドの現在の進行角度を取得
        qWorldRoll = glm::angleAxis(world->GetRotator().GetProgressAngle(), world->GetRotator().getBaseAxis());

        mRoll = qWorldRoll;
    }

    currentTransform.direction = glm::normalize(target->getPosition() - currentTransform.position);

    if(qWorldRoll == glm::quat(1, 0, 0, 0))
    {
        orientation = qYaw * qPitch * orientation;
        offset = orientation * offsetBase;
        currentTransform.position = target->getPosition() + offset;
        currentTransform.up = up;
    }else{
        orientation = qYaw * qPitch * mRoll;
        offset = orientation * offsetBase;
        currentTransform.position = target->getPosition() + offset;
        currentTransform.up = orientation * up;
    }

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
    glm::vec3 front = orientation * ( -world->GetRotator().getBaseAxis() );

    //Helper::printVec3("Camera", "CurrCamFront", front);

    return front;
}

const glm::vec3 Camera::getCurrentCameraRight() const
{
    glm::vec3 upAxis = -world->GetCurrentGravityDir();
    glm::vec3 flatForward = getCurrentCameraFront();
    glm::vec3 right = glm::normalize(glm::cross(flatForward, upAxis));

    return right;
}

void Camera::StartRoll(float angleDeg, float durationSec)
{
    isRolling = true;
    rollTimer = 0.0f;
    rollDuration = durationSec;
    rollStartAngle = 0.0f;
    rollTargetAngle = angleDeg;
}

glm::quat Camera::getYaw() const
{
    glm::vec3 up = -world->GetCurrentGravityDir();
    glm::vec3 forward = orientation * (-world->GetRotator().getBaseAxis());

    // forwardベクトルを水平面（Yaw）に射影
    glm::vec3 flatForward = forward - glm::dot(forward, up) * up;

    if (glm::length(flatForward) < 0.001f)
    {
        return glm::quat(1, 0, 0, 0); // fallback: 単位クォータニオン
    }

    flatForward = glm::normalize(flatForward);

    return glm::quatLookAt(flatForward, up);
}

const glm::vec3 Camera::getCurrentPlayerFront() const
{
    return target->getfront();
}