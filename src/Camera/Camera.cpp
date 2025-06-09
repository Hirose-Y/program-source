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
    Initialize(currentTransform, projection);

    rotation.yawAxis = glm::vec3(0, 1, 0);
    rotation.yawAngle = 0.0f;
    rotation.yawInput = 0.0f;

    rotation.pitchAxis = glm::vec3(1, 0, 0);
    rotation.pitchAngle = 30.0f;
    rotation.pitchInput = 0.0f;

    offsetAxis = glm::vec3(0, 0, 1);
    distance = 4.0f;

    provisonalTransform = currentTransform;
    provisionalRotation = rotation;

    world->AddCallback(
        "RotateStartCallback_Camera",
        
        [this]() 
        {
            Helper::printStr("Camera", "-----------Camera Rotation Start--------");

            glm::vec3 cameraOffset = currentTransform.position - target->getPosition();
            provisonalTransform.position = cameraOffset; // 相対ベクトルとして保存
            provisonalTransform.direction = currentTransform.direction;
            provisonalTransform.up = Helper::KeepMaxComponent(currentTransform.up);
        });

    world->AddCallback(
        "RotateFinishCallback_Camera", 
        
        [this]()
        {
            provisonalTransform.direction = currentTransform.direction;
            provisonalTransform.up = Helper::KeepMaxComponent(currentTransform.up);
            
            rotation.yawAxis = Helper::KeepMaxComponent(currentTransform.up);
            rotation.pitchAxis = getCurrentCameraRight();

            offsetAxis = world->GetBaseAxis();

            Helper::printVec3("Camera", "offset", offsetAxis);
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

void Camera::ProcessInput(const PlayInputActions* input)
{
    rotation.yawInput = 0.0f;
    rotation.pitchInput = 0.0f;
    input->camera.ShouldRotationYaw(rotation.yawInput);
    input->camera.ShouldRotationPitch(rotation.pitchInput);

    if(input->camera.ResetYawAndPitch())
    {
        // glm::vec3 gravity = world->GetCurrentGravityDir();
        // glm::vec3 flatForward = getCurrentCameraFront();
        // glm::vec3 rightAxis = glm::normalize(glm::cross(gravity, flatForward));

        // rotation.yawAxis = -gravity;
        // rotation.yawAngle = 0.0f;

        // rotation.pitchAxis = rightAxis;
        // rotation.pitchAngle = 30.0f;

        // glm::mat4 yawRot   = glm::rotate(glm::mat4(1.0f), glm::radians(-rotation.yawAngle), rotation.yawAxis);
        // glm::mat4 pitchRot = glm::rotate(glm::mat4(1.0f), glm::radians(-rotation.pitchAngle), rotation.pitchAxis);
        // glm::vec3 baseOffset = offsetAxis * distance;

        // glm::vec3 offset = glm::vec3(yawRot * pitchRot * glm::vec4(baseOffset, 0.0f));

        // currentTransform.position = target->getPosition() + offset;
        // currentTransform.direction = glm::normalize(target->getPosition() - currentTransform.position);
        // currentTransform.up = -gravity;
    }
}

void Camera::Update(float deltaTime)
{
    if (!target) return;

    if(world->isWorldRotation())
    {
        RotateCamera();
        updateViewMatrix();
        return;
    }

    UpdateYawPitch(deltaTime);
    UpdateTransform();
    updateViewMatrix();
}

void Camera::UpdateStableTransform()
{
    provisonalTransform = currentTransform;
}

void Camera::UpdateYawPitch(float deltaTime)
{
    if (rotation.yawInput == 0.0f && rotation.pitchInput == 0.0f) return;

    rotation.yawAngle += rotation.yawInput * 90.0f * deltaTime;
    rotation.yawAngle = fmod(rotation.yawAngle, 360.0f);
    if (rotation.yawAngle < 0) rotation.yawAngle += 360.0f;

    rotation.pitchAngle += rotation.pitchInput * 30 * deltaTime;

    if (rotation.pitchAngle > 89.0f) rotation.pitchAngle = 89.0f;
    if (rotation.pitchAngle < -89.0f) rotation.pitchAngle = -89.0f;

}

void Camera::RotateCamera()
{
    glm::vec3 upAxis = glm::vec3(world->GetWorldRotation() * glm::vec4(glm::vec3(0, 1, 0), 0));
    glm::vec3 cameraOffsetAxis = glm::vec3(world->GetWorldRotation() * glm::vec4(glm::vec3(0, 0, 1), 0));

    glm::vec3 forwardRef = getCurrentCameraFront();
    if (glm::abs(glm::dot(forwardRef, upAxis)) > 0.99f)
    {
        std::cout << "forward is almost parallel to upAxis" << std::endl;
        forwardRef = glm::vec3(1, 0, 0);
    }

    glm::vec3 sideAxis = glm::normalize(glm::cross(forwardRef, upAxis));

    glm::vec3 yawAxis = glm::vec3(world->GetWorldRotation() * glm::vec4(rotation.yawAxis, 0));
    glm::vec3 pitchAxis = glm::vec3(world->GetWorldRotation() * glm::vec4(rotation.pitchAxis, 0));

    glm::mat4 yawRot   = glm::rotate(glm::mat4(1.0f), glm::radians(-rotation.yawAngle), yawAxis);
    glm::mat4 pitchRot = glm::rotate(glm::mat4(1.0f), glm::radians(-rotation.pitchAngle), pitchAxis);
    glm::vec3 baseOffset = cameraOffsetAxis * distance;

    glm::vec3 offset = glm::vec3(yawRot * pitchRot * glm::vec4(baseOffset, 0.0f));

    currentTransform.position = target->getPosition() + offset;
    currentTransform.direction = glm::normalize(target->getPosition() - currentTransform.position);
    currentTransform.up = upAxis;

    updateViewMatrix();
}

void Camera::UpdateTransform()
{
    glm::vec3 cameraRight = getCurrentCameraRight();    

    glm::mat4 yawRot   = glm::rotate(glm::mat4(1.0f), glm::radians(-rotation.yawAngle), rotation.yawAxis);
    glm::mat4 pitchRot = glm::rotate(glm::mat4(1.0f), glm::radians(-rotation.pitchAngle), rotation.pitchAxis);
    glm::vec3 baseOffset = offsetAxis * distance;
    glm::vec3 offset = glm::vec3(yawRot * pitchRot * glm::vec4(baseOffset, 0.0f));

    currentTransform.position = target->getPosition() + offset;
    currentTransform.direction = glm::normalize(target->getPosition() - currentTransform.position);
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

void Camera::SetDirection(glm::vec3 dir)
{
    currentTransform.direction = glm::normalize(dir);
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

const glm::vec3 Camera::getCameraFront() const
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
    glm::vec3 flatForward = Helper::NormalizeOrZero( dir - glm::dot(dir, gravity) * gravity );

    // 長さが0に近いときはfallbackする
    if (glm::length(flatForward) < 0.001f)
    {
        // fallback: worldのZ軸を使う
        return glm::normalize(glm::cross(gravity, glm::vec3(1, 0, 0)));
    }

    //Helper::printVec3("Camera", "CurrCamFront", flatForward);

    return glm::normalize(flatForward);
}

const glm::vec3 Camera::getCurrentCameraRight() const
{
    glm::vec3 upAxis = currentTransform.up;
    glm::vec3 flatForward = getCurrentCameraFront();
    glm::vec3 right = glm::normalize(glm::cross(flatForward, upAxis));

    return right;
}
