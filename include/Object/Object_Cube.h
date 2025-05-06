#ifndef CUBE_H
#define CUBE_H

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

class Cube : public Object
{
public:
    Cube(Shader* shaderProgram, World* world_, ObjectInfo info_, std::unique_ptr<Behavior> behavior);
    ~Cube();

    void Initialize() override;
    void Update(float deltaTime) override;
    void draw(Camera* camera, Light* light) override;
    
    Collider* GetCollider() const override { return collider.get(); }
    ObjectType GetObjectType() const override { return ObjectType::CUBE; }
    glm::mat4 GetDeltaMatrix() const override { return modelMatrix * glm::inverse(previousmodelMatrix); }
    int GetObjectID() const override { return info.id; }
private:
    ObjectInfo info;
    glm::mat4 previousmodelMatrix;
    glm::mat4 modelMatrix;
    glm::mat4 worldModel;

    Shader* shader;
    World* world;

    std::unique_ptr<Collider> collider;
    std::unique_ptr<Behavior> movebehavior;
    
    float angle = 0.0f;
};

#endif /* CUBE_H */