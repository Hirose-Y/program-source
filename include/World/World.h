#ifndef WORLD_H
#define WORLD_H

#include <string>
#include "Core/GLHeaders.h"
#include "World/WorldRotator.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include "Utils/CallbackRegistry.h"

class PlayInputActions;
class Camera;

class World
{
public:
    World();
    ~World();

    // 実行したいコールバック関数を登録
    void AddCallback(const std::string& name, std::function<void()> cb) {
        callbackFunctions.Add(name, cb);
    }

    void RemoveCallback(const std::string& name) {
        callbackFunctions.Remove(name);
    }

    void Initialize(glm::vec3 pos, glm::vec3 sc);

    void ProcessInput(PlayInputActions* input);
    void Update(float deltaTime);

    void RotateReset();

    void ExecuteCallback(const std::string& name);

    float Gravity() const { return gravity; }

    glm::mat4 GetWorldRotation() const { return glm::mat4_cast(orientation); }
    glm::vec3 GetCurrentGravityDir() const { return rotator.GetCurrentGravityDir(); }
    glm::vec3 GetBaseAxis() const {return rotator.getBaseAxis(); }
    glm::vec3 GetWorldSize() const { return size; }

    int GetRotLimit() const { return rotLimit; }
    WorldRotator GetRotator() const { return rotator; }

    bool isStartRotation() const { return rotator.IsStart(); }
    bool isWorldRotation() const { return rotator.IsRotating(); }

    Camera* GetCamera() const { return camera; }
    void SetCamera(Camera* camera_);
private:
    glm::quat orientation;
    glm::vec3 size;

    float gravity;
    Camera* camera;

    WorldRotator rotator;
    CallbackRegistry callbackFunctions;

    int rotLimit;           //接地するまで何回回転できるか
};

#endif /* WORLD_H */