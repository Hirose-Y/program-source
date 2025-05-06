#ifndef PLAYER_H
#define PLAYER_H

#include "GLHeaders.h"
#include "Object/Object.h"
#include "Behavior/Behavior.h"
#include <memory>
#include <string>

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

    void ProcessInput(const PlayInputActions& input);

    void Initialize() override;
    void Update(float deltaTime) override;
    void draw(Camera* camera, Light* light) override;

    glm::vec3 getPosition() const { return position; }
    ObjectType GetObjectType() const override { return ObjectType::PLAYER; }
    glm::mat4 GetDeltaMatrix() const override { return modelMatrix * glm::inverse(previousmodelMatrix); }
    void ClearStage();

    bool isDead() const { return dead; }
    bool GetONGround() const { return isOnGround; }
    int GetObjectID() const override { return ID; }
    int GetItemCounter() const { return itemCounter; }
private:
    void move(float deltaTime);
    void Collision();
    void FollowMovingFloor();

    bool CheckGroundByRay();
    void ApplyWorldRotation(const glm::mat4& rotationDelta);

    glm::vec3 position;
    glm::vec3 scale;
    glm::mat4 previousmodelMatrix;
    glm::mat4 modelMatrix;
    glm::mat4 worldModel;
    glm::vec3 jump;

    Shader* shader;
    World* world;
    Camera* camera;

    std::unique_ptr<Collider> collider;
    glm::vec3 speed;

    bool isOnGround;
    bool isOnFloor(Collider* player, Collider* stage);
    bool dead;
    std::vector<Object*> stage;
    int ID;

    int itemCounter;
};

#endif /* PLAYER_H */