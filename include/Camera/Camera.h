#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "Core/GLHeaders.h"
#include "Camera/CameraVariables.h"
#include "Object/Object_Player.h"

class World;
class PlayInputActions;

class Camera
{
private:
    struct CameraRotation {
        glm::vec3 yawAxis;
        float yawAngle;
        float yawInput;

        glm::vec3 pitchAxis;
        float pitchAngle;
        float pitchInput;
    };
public:
    Camera(CameraTransform trans, CameraProjection proj, World* world_);
    ~Camera();

    void Initialize(CameraTransform trans, CameraProjection proj);
    void ProcessInput(const PlayInputActions* input);
    void Update(float deltaTime);
    void UpdateStableTransform();   //回転終了後に更新

    void SetTarget(Player* player);

    void SetPosition(glm::vec3 pos);
    void SetDirection(glm::vec3 dir);
    void SetAspectRatio(float aspect);

    const glm::mat4 getViewMatrix() const { return viewMatrix; }
    const glm::mat4 getProjectionMatrix() const { return projectionMatrix; }

    const glm::vec3 getCameraPos() const { return currentTransform.position; }
    const glm::vec3 getCameraFront() const;
    const glm::vec3 getCurrentCameraFront() const;
    const glm::vec3 getCurrentCameraRight() const;
    const glm::vec3 getUPDirection() const { return provisonalTransform.up; }

private:
    void updateViewMatrix();
    void UpdateYawPitch(float deltaTime);
    void RotateCamera();
    void UpdateTransform();
    void updateProjectionMatrix();

    CameraTransform currentTransform; // 描画・回転中で更新する用
    CameraTransform provisonalTransform; // 回転開始における初期値用
    CameraProjection projection;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    CameraRotation rotation;
    CameraRotation provisionalRotation;

    glm::vec3 offsetAxis;
    float distance;

    Player* target;
    World* world;
};

#endif /* CAMERA_H */
