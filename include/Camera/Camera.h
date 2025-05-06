#ifndef CAMERA_H
#define CAMERA_H

#include "GLHeaders.h"
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
    void ProcessInput(const PlayInputActions& input);
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
    const glm::vec3 getUPDirection() const { return stableTransform.up; }

private:
    void updateViewMatrix();
    void updateProjectionMatrix();

    CameraTransform currentTransform; // 描画・回転用
    CameraTransform stableTransform;  // 入力・参照用
    CameraProjection projection;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    float yaw;
    float yawInput;
    float pitch;
    float pitchInput;

    float distance;

    Player* target;
    World* world;
};

#endif /* CAMERA_H */
