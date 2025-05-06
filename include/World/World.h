#ifndef WORLD_H
#define WORLD_H

#include "GLHeaders.h"
#include "World/WorldRotator.h"

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include "Utils/CallbackRegistry.h"

class PlayInputActions;
class Camera;

class World
{
public:
    World();
    ~World();

    // 回転が終了したときに実行したい関数を登録
    void AddOnRotateFinishCallback(const std::string& name, std::function<void()> cb) {
        onRotateFinish.Add(name, cb);
    }

    void RemoveOnRotateFinishCallback(const std::string& name) {
        onRotateFinish.Remove(name);
    }


    void Initialize(glm::vec3 pos, glm::vec3 sc);

    void ProcessInput(const PlayInputActions& input);
    void Update(float deltaTime);

    void RotateCamera();
    void RotateGravity();
    void RotateReset();

    float Gravity() const { return gravity; }

    glm::mat4 GetPreviousWorld() const { return prevWorldMatrix; }
    glm::mat4 GetWorldRotation() const { return worldMatrix; }
    glm::vec3 GetCurrentGravityDir() const { return rotator.GetCurrentGravityDir(); }
    glm::vec3 GetPreviousGravityDir() const { return rotator.GetPreviousGravityDir(); }
    glm::vec3 GetWorldSize() const { return size; }

    int GetRotLimit() const { return rotLimit; }
    int GetGravityIndex() const { return rotator.GetGravityIndex(); }
    bool isWorldRotation() const { return rotator.IsRotating(); }

    Camera* GetCamera() const { return camera; }
    void SetCamera(Camera* camera_);
private:
    void AjastMatrix(glm::mat4& mat);
    glm::mat4 prevWorldMatrix;
    glm::mat4 worldMatrix;
    glm::vec3 gravityDirection;
    glm::vec3 size;

    float gravity;
    Camera* camera;

    WorldRotator rotator;
    CallbackRegistry onRotateFinish;

    int rotLimit;           //接地するまで何回回転できるか
    // SetRotateFinishCallback()に登録した関数が格納されている変数
    //std::unordered_map<std::string, std::function<void()>> onRotateFinish; 
    //std::vector<std::function<void()>> onRotateFinish;
};

#endif /* WORLD_H */