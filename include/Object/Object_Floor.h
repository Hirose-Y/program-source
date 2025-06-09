#ifndef FLOOR_H
#define FLOOR_H

#include <string>
#include "Core/GLHeaders.h"
#include "Object/Object.h"
#include "Object/ObjectInfo.h"
#include "Behavior/Behavior.h"
#include <memory>

class Camera;
class Collider;
class Light;
class World;
class Shader;

class Floor : public Object
{
public:
    Floor(Shader* shaderProgram, World* world_, ObjectInfo info_, std::unique_ptr<Behavior> behavior);
    ~Floor();

    void Initialize() override;
    void Update(float deltaTime) override;
    void draw(Camera* camera, Light* light) override;
    
    Collider* GetCollider() const override { return collider.get(); }
    ObjectType GetObjectType() const override { return ObjectType::FLOOR; }
    bool IsTransparent() const override { return info.isTransparency; }
    glm::mat4 GetDeltaMatrix() const override { return modelMatrix * glm::inverse(previousmodelMatrix); }
    int GetObjectID() const override { return info.id; }

    void Transparent(bool flag) override { info.isTransparency = flag; flag ? info.transparency = 0.3f : info.transparency = 1.0f; }
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

#endif /* FLOOR_H */