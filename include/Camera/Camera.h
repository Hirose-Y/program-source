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
public:
    Camera(CameraTransform trans, CameraProjection proj, World* world_);
    ~Camera();

    void Initialize(CameraTransform trans, CameraProjection proj);
    void ProcessInput(PlayInputActions* input);
    void Update(float deltaTime);

    void SetTarget(Player* player);
    void SetPosition(glm::vec3 pos);
    void SetAspectRatio(float aspect);

    void StartRoll(float angleDeg, float durationSec);

    const glm::mat4 getViewMatrix() const { return viewMatrix; }
    const glm::mat4 getProjectionMatrix() const { return projectionMatrix; }

    const glm::vec3 getCameraPos() const { return currentTransform.position; }
    const glm::vec3 getProvCameraFront() const;
    const glm::vec3 getCurrentCameraFront() const;
    const glm::vec3 getCurrentCameraRight() const;
    const glm::vec3 getUPDirection() const { return provisonalTransform.up; }

private:
    void updateViewMatrix();
    void updateProjectionMatrix();
    void RollAroundViewAxis(float angleDegrees);

    CameraTransform currentTransform; // 描画・回転中で更新する用
    CameraTransform provisonalTransform; // 回転開始における初期値用
    CameraProjection projection;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    glm::quat orientation;  // 回転の姿勢
    glm::vec3 offsetBase;   // プレイヤー基準のオフセット
    float distance;         // 距離

    float yawInput;
    float pitchInput;

    Player* target;
    World* world;

    // roll補間用
    bool isRolling = false;
    float rollTimer = 0.0f;
    float rollDuration = 0.0f;
    float rollStartAngle = 0.0f;
    float rollTargetAngle = 0.0f;
};

#endif /* CAMERA_H */
