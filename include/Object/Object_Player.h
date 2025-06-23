#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Core/GLHeaders.h"
#include "Object/Object.h"
#include "Behavior/Behavior.h"
#include <memory>
#include "Math/Transform.h"

class Collider;
class Camera;
class Light;
class Window;
class World;
class Shader;
class PlayInputActions;

class Player : public Object
{
public:
    Player(int id, Shader* shaderProgram, glm::vec3 pos, World* world_, Camera* camera_);
    ~Player();

    void AttachmentStage(Object* stageObject);

    void ProcessInput(PlayInputActions* input);

    void Initialize() override;
    void Update(float deltaTime) override;
    void draw(Camera* camera, Light* light) override;

    Transform GetTransform() const { return transform; }
    glm::quat GetYaw() const { return qYaw; }
    ObjectType GetObjectType() const override { return ObjectType::PLAYER; }
    glm::mat4 GetDeltaMatrix() const override { return transform.getModelMatrix() * glm::inverse(previousmodelMatrix); }
    glm::mat4 GetMatrix() const { return transform.getModelMatrix(); }
    void ClearStage();

    bool isDead() const { return dead; }
    bool GetONGround() const { return isOnGround; }
    int GetObjectID() const override { return ID; }
    int GetItemCounter() const { return itemCounter; }

    glm::vec3 getfront() const;
private:
    void move(float deltaTime);
    void Collision();
    void FollowMovingFloor();

    bool CheckGroundByRay();
    void UpdateTransparencyByRay(Camera* camera);

    Transform transform;
    glm::mat4 previousmodelMatrix;
    glm::mat4 worldModel;
    glm::vec3 jump;

    Shader* shader;
    World* world;
    Camera* camera;

    std::unique_ptr<Collider> collider;
    glm::vec3 speed;

    bool isOnGround;
    bool dead;
    std::vector<Object*> stage;
    int ID;

    int itemCounter;
    
    float yawInput;
    glm::quat qYaw;
};

#endif /* PLAYER_H */