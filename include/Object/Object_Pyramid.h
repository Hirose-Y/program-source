#ifndef PYRAMID_H
#define PYRAMID_H

#include "GLHeaders.h"
#include "Object/Object.h"
#include "Object/ObjectInfo.h"
#include "Behavior/Behavior.h"
#include <memory>

class Collider;
class Camera;
class Light;
class World;
class Shader;

class Pyramid : public Object
{
public:
    Pyramid(Shader* shaderProgram, World* world_, ObjectInfo info_, std::unique_ptr<Behavior> behavior);
    ~Pyramid();

    void Initialize() override;
    void Update(float deltaTime) override;
    void draw(Camera* camera, Light* light) override;

    Collider* GetCollider() const override { return collider.get(); }
    ObjectType GetObjectType() const override { return ObjectType::PYRAMID; }
    glm::mat4 GetDeltaMatrix() const override { return modelMatrix * glm::inverse(previousmodelMatrix); }
    int GetObjectID() const override { return info.id; }

    bool isdraw;
private:
    ObjectInfo info;
    glm::mat4 previousmodelMatrix;
    glm::mat4 modelMatrix;
    glm::mat4 worldModel;

    std::unique_ptr<Collider> collider;
    std::unique_ptr<Behavior> movebehavior;
    
    Shader* shader;
    World* world;

    float angle;
    glm::vec3 axis;
};

#endif /* PYRAMID_H */