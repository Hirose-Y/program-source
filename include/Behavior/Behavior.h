#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <string>
#include "Core/GLHeaders.h"
#include "Math/Transform.h"
#include <memory>
#include <vector>

class Behavior
{
public:
    virtual ~Behavior() = default;
    virtual void Update(Transform& transform, float deltaTime) = 0;
};

class RotateBehavior : public Behavior
{
public:
    RotateBehavior(glm::vec3 axis_, float speed_);
    void Update(Transform& transform, float deltaTime) override;

private:
    glm::vec3 axis;
    float speed;
};

class TranslateBehavior : public Behavior
{
public:
    TranslateBehavior(glm::vec3 trans_, float val_);
    void Update(Transform& transform, float deltaTime) override;

private:
    glm::vec3 translate;
    float val;
};

class RoundBehavior : public Behavior
{
public:
    RoundBehavior(glm::vec3 axis_, float val_);
    void Update(Transform& transform, float deltaTime) override;

private:
    glm::vec3 axis;
    float val;
};

class ScaledBehavior : public Behavior
{
public:
    ScaledBehavior(glm::vec3 scale_, float val_);
    void Update(Transform& transform, float deltaTime) override;
private:
    glm::vec3 scale;
    float val;
};

class CompositeBehavior : public Behavior
{
public:
    void addBehavior(std::unique_ptr<Behavior> behavior);

    void Update(Transform& transform, float deltaTime) override;
private:
    std::vector<std::unique_ptr<Behavior>> behaviors;
};

#endif /* BEHAVIOR_H */