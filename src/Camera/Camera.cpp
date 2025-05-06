#include "Camera/Camera.h"
#include "Object/Object_Player.h"
#include "World/World.h"

#include "Input/InputSystem.h"
#include "InputActions/Context/InputContext_Play.h"
#include <iostream>

#include "Utils/Helper.h"

Camera::Camera(CameraTransform trans, CameraProjection proj, World* world_)
: currentTransform(trans), stableTransform(trans), projection(proj), target(nullptr), world(world_)
{
    Initialize(currentTransform, projection);

    Helper::printVec3("Camera", "currTrans.pos: ", currentTransform.position);
    Helper::printVec3("Camera", "currTrans.dir: ", currentTransform.direction);
    Helper::printVec3("Camera", "currTrans.up", currentTransform.up);
    Helper::printVec3("Camera", "stableTrans.pos", stableTransform.position);
    Helper::printVec3("Camera", "stableTrans.dir", stableTransform.direction);
    Helper::printVec3("Camera", "stableTrans.up", stableTransform.up);

    yaw = 0.0f;
    yawInput = 0.0f;
    pitch = 30.0f;
    distance = 4.0f;

    world->AddOnRotateFinishCallback(
        "Camera",

        [this]() 
        {
            UpdateStableTransform();
        }
    );
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

void Camera::ProcessInput(const PlayInputActions& input)
{
    yawInput = 0.0f;
    pitchInput = 0.0f;
    input.camera.ShouldRotationYaw(yawInput);
    input.camera.ShouldRotationPitch(pitchInput);
    
    if(input.camera.ResetYawAndPitch())
    {
        yaw = 0.0f;
        pitch = 30.0f;

        glm::vec3 gravity = world->GetCurrentGravityDir();
        glm::vec3 dir = stableTransform.direction;

        // dirベクトルから重力成分を取り除いて水平成分だけ取り出す
        glm::vec3 flatForward = Helper::KeepMaxComponent(dir - glm::dot(dir, gravity) * gravity);
        if (glm::abs(glm::dot(flatForward, -gravity)) > 0.99f) flatForward = glm::vec3(1, 0, 0);

        glm::vec3 sideAxis = glm::normalize(glm::cross(-gravity, flatForward));

        glm::mat4 yawRot   = glm::rotate(glm::mat4(1.0f), glm::radians(-yaw), -gravity);
        glm::mat4 pitchRot = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), sideAxis);
        glm::vec3 baseOffset = glm::vec3(0, 0, distance);

        glm::vec3 offset = glm::vec3(yawRot * pitchRot * glm::vec4(baseOffset, 0.0f));

        currentTransform.position = target->getPosition() + offset;
        currentTransform.direction = glm::normalize(target->getPosition() - currentTransform.position);
        currentTransform.up = -gravity;

        stableTransform = currentTransform;
    }
}

void Camera::Update(float deltaTime)
{
    if (!target) return;

    yaw += yawInput * 90.0f * deltaTime;
    yaw = fmod(yaw, 360.0f);
    if (yaw < 0) yaw += 360.0f;

    pitch += pitchInput * 30 * deltaTime;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 upAxis = glm::vec3(world->GetWorldRotation() * glm::vec4(0, 1, 0, 0));

    glm::vec3 f = getCameraFront();
    glm::vec3 front = getCurrentCameraFront();
    Helper::printVec3("Camera", "prevFront", f);
    Helper::printVec3("Camera", "currFront", front);
    glm::vec3 forwardRef = f;
    if (glm::abs(glm::dot(forwardRef, upAxis)) > 0.99f)
        forwardRef = glm::vec3(1, 0, 0);

    glm::vec3 sideAxis = glm::normalize(glm::cross(upAxis, forwardRef));

    glm::mat4 yawRot   = glm::rotate(glm::mat4(1.0f), glm::radians(-yaw), upAxis);
    glm::mat4 pitchRot = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), sideAxis);
    glm::vec3 baseOffset = glm::vec3(0, 0, distance);

    glm::vec3 offset = glm::vec3(yawRot * pitchRot * glm::vec4(baseOffset, 0.0f));

    currentTransform.position = target->getPosition() + offset;
    currentTransform.direction = glm::normalize(target->getPosition() - currentTransform.position);
    currentTransform.up = upAxis;

    updateViewMatrix();
}

void Camera::UpdateStableTransform()
{
    stableTransform = currentTransform;
}

void Camera::SetTarget(Player* player)
{
    target = player;

    glm::vec3 upAxis = glm::vec3(world->GetWorldRotation() * glm::vec4(0, 1, 0, 0));

    glm::vec3 forwardRef = glm::vec3(0, 0, -1);
    if (glm::abs(glm::dot(forwardRef, upAxis)) > 0.99f)
        forwardRef = glm::vec3(1, 0, 0);

    glm::vec3 sideAxis = glm::normalize(glm::cross(upAxis, forwardRef));

    glm::mat4 yawRot   = glm::rotate(glm::mat4(1.0f), glm::radians(-yaw), upAxis);
    glm::mat4 pitchRot = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), sideAxis);
    glm::vec3 baseOffset = glm::vec3(0, 0, distance);

    glm::vec3 offset = glm::vec3(yawRot * pitchRot * glm::vec4(baseOffset, 0.0f));

    currentTransform.position = target->getPosition() + offset;
    currentTransform.direction = glm::normalize(target->getPosition() - currentTransform.position);
    currentTransform.up = upAxis;

    stableTransform = currentTransform;
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
    glm::vec3 dir = stableTransform.direction;

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
    glm::vec3 flatForward = dir - glm::dot(dir, gravity) * gravity;

    // 長さが0に近いときはfallbackする
    if (glm::length(flatForward) < 0.001f)
    {
        // fallback: worldのZ軸を使う
        return glm::normalize(glm::cross(gravity, glm::vec3(1, 0, 0)));
    }

    return glm::normalize(flatForward);
}
