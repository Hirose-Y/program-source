#ifndef WORLDROTATOR_H
#define WORLDROTATOR_H

#include <string>
#include "Core/GLHeaders.h"

class World;

class WorldRotator
{
public:
    enum class State
    {
        Idle,       // 待機中
        Start,      // 回転始め(1フレームのみ)
        Rotating,   // 回転中
        Finish      // 回転終わり(1フレームのみ)
    };

    WorldRotator(World* world_);
    ~WorldRotator();

    void StartRotation(int direction, glm::vec3 axis_, float target_, float speed_);
    void Update(float deltaTime, glm::mat4& worldMatrix);

    void CalcGravityDir();
    void Reset();

    bool IsStart() const { return state == State::Start; }
    bool IsRotating() const { return state == State::Start || state == State::Rotating; }
    bool IsFinished() const { return state == State::Finish; }

    World* GetWorld() const { return world; }
    State GetState() const { return state; }
    int GetGravityIndex() const { return gravityIndex; }
    glm::vec3 GetCurrentGravityDir() const { return currentGravityDir; }
    glm::vec3 GetPreviousGravityDir() const { return previoursGravityDir; }

    glm::vec3 getBaseAxis() const { return baseaxis; }
    void setBase(const glm::vec3 base) { baseaxis = base; }

    float GetProgressAngle() const { return progress; } // すでにラジアン
    glm::vec3 GetAxis() const { return axis; }
private:
    World* world;
    State state;

    glm::vec3 axis;         //回転軸（Z軸のみ）
    glm::vec3 baseaxis;
    glm::vec3 currentGravityDir;
    glm::vec3 previoursGravityDir;
    float targetAngle;      //回転の最終値
    float rotationSpeed;    //回転速度
    float progress;

    int rotCounter;
    int gravityIndex;
};

#endif /* WORLDROTATOR_H */