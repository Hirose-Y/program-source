#include "GLHeaders.h"
#include "Object/ObjectInfo.h"
#include "Object/Object_Player.h"
#include "Object/Object_Pyramid.h"
#include "Collider/Collider_OBB.h"
#include "Window.h"
#include "Shader.h"
#include "World/World.h"
#include "Input/InputSystem.h"
#include "InputActions/Context/InputContext_Play.h"
#include "Camera/Camera.h"
#include "Light.h"

#include <iostream>
#include <vector>
#include <cmath>

#include "Utils/Helper.h"

Player::Player(int id, Shader* shaderProgram, glm::vec3 pos, World* world_, Camera* camera_) 
: Object("Assets/obj/cube.obj")
, position(pos), shader(shaderProgram), dead(false)
, speed(glm::vec3(0.0f, 0.0f, 0.0f)), jump(glm::vec3(0.0f, 0.0f, 0.0f))
{
    world = world_;
    camera = camera_;
    ID = id;
    itemCounter = 0;
    isOnGround = false;
    Initialize();

    // コールバック関数の登録
    world->AddOnRotateFinishCallback(
        "Player",

        [this]() { 
            jump = world->GetCurrentGravityDir() * 5.0f; 
            Helper::printVec3("Player", "position", position);
        }
    );
}

Player::~Player()
{

}

void Player::Initialize()
{
    scale = glm::vec3(0.5f, 0.5f, 0.5f);
    modelMatrix = glm::translate(glm::mat4(1.0f), position) 
                * glm::scale(glm::mat4(1.0f), scale);

    //Helper::printVec3("Player", "position", position);
    
    collider = std::make_unique<OBB>(modelMatrix);
}


void Player::ProcessInput(const PlayInputActions& input)
{
    glm::vec3 gravityDir = world->GetCurrentGravityDir(); //重力の方向
    
    // カメラの前方向をワールド空間に変換
    glm::vec3 camDir = camera->getCameraFront();
    glm::vec3 forward = camera->getCurrentCameraFront();//glm::normalize(camDir - glm::dot(camDir, gravityDir) * gravityDir);
    //Helper::printVec3("camera->getCameraFront()", "", camera->getCameraFront());
 //   Helper::printVec3("Player", "forward", forward);
    glm::vec3 right = glm::normalize(glm::cross(gravityDir, forward));
    
    // 入力方向ベクトルの構成
    glm::vec3 moveDir = input.player.GetMoveDirection(forward, right);
    if (glm::length(moveDir) > 0.0f)
    {
        moveDir = glm::normalize(moveDir);
    }
    
    speed = moveDir * 3.0f;

    if (input.player.ShouldJump() && isOnGround)
    { 
        jump = -1.0f * gravityDir * 10.0f;  // ジャンプは重力と逆向きに力を与える
        
        isOnGround = false;
    }
    //std::cout << "ongr : ( " << isOnGround << std::endl;
    
}

void Player::Update(float deltaTime)
{
    //std::cout << "position : ( " << position.x << ", " << position.y << ", " << position.z << " )" << std::endl;
    
    if(world->isWorldRotation()) return;

    previousmodelMatrix = modelMatrix;
    
    jump += world->GetCurrentGravityDir() * 20.0f * deltaTime;
    //std::cout << "jump : ( " << jump.x << ", " << jump.y << ", " << jump.z << " )" << std::endl;
    // 最大落下制限を方向で制限

    float maxFallSpeed = 10.0f;
    float jumpspeed = glm::length(jump);
    if (jumpspeed > maxFallSpeed) {
        jump = glm::normalize(jump) * maxFallSpeed;
    }

    move(deltaTime);
    Collision();
    FollowMovingFloor();

    modelMatrix = glm::translate(glm::mat4(1.0f), position)                
                 *glm::scale(glm::mat4(1.0f), scale);

    collider->Update(modelMatrix);

    //std::cout << "position : ( " << position.x << ", " << position.y << ", " << position.z << " )" << std::endl;
    if( position.y < -world->GetWorldSize().y || position.y > world->GetWorldSize().y ||
        position.x < -world->GetWorldSize().x || position.x > world->GetWorldSize().x || 
        position.z < -world->GetWorldSize().z || position.z > world->GetWorldSize().z  )
    {
        dead = true;
    }
}

void Player::draw(Camera* camera, Light* light)
{
    shader->use();

    // シェーダーの uniform 変数にモデル行列を渡す(vertexシェーダーのuniform変数の場所を取得)
    shader->SetMat4("model", modelMatrix);
    shader->SetMat4("view", camera->getViewMatrix());
    shader->SetMat4("projection", camera->getProjectionMatrix());

    glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
    shader->SetMat3("normalMatrix", normalMatrix);

    // 光の設定
    shader->SetVec3("lightDir", glm::normalize(light->lightDir));
    shader->SetVec3("lightColor", light->lightColor);

    shader->SetVec3("pointLightPos", light->position);
    shader->SetVec3("pointLightColor", light->lightColor);

    // カメラの位置
    shader->SetVec3("viewPos", camera->getCameraPos());

    // オブジェクトの色
    shader->SetVec3("objectColor", glm::vec3(1.0f, 0.8f, 0.3f));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3); // 描画
    glBindVertexArray(0);
}

void Player::AttachmentStage(Object* stageObject)
{
    stage.push_back(stageObject);
}

void Player::move(float deltaTime)
{
    position += speed * deltaTime;
    position += jump * deltaTime;

    modelMatrix = glm::translate(glm::mat4(1.0f), position) 
                * glm::scale(glm::mat4(1.0f), scale);

    collider->Update(modelMatrix);
}

void Player::Collision()
{
    std::vector<int> removeIDs;

    for(auto s : stage)
    {
        if(!collider->checkCollision(*s->GetCollider())) { continue; }

        //衝突した四角錘の当たり判定を削除&描画フラグをfalseに
        if(s->GetObjectType() == ObjectType::PYRAMID)
        {
            auto pyramid = dynamic_cast<Pyramid*>(s);
            int ID = pyramid->GetObjectID();
            pyramid->isdraw = false;
            itemCounter++;
            removeIDs.push_back(ID);
        }

        glm::vec3 correction = collider->resolveCollision(*s->GetCollider());

        if(glm::length(correction) > 0.0f)
        {
            position -= correction;
        }
    }

    // 衝突後に削除処理を行う（1フレーム遅れて消える）
    stage.erase(
        std::remove_if(stage.begin(), stage.end(),
            [&removeIDs](Object* obj)
            {
                return obj->GetObjectType() == ObjectType::PYRAMID &&
                       std::find(removeIDs.begin(), removeIDs.end(), obj->GetObjectID()) != removeIDs.end();
            }),
        stage.end()
    );
}

bool Player::isOnFloor(Collider* player, Collider* stage)
{
    isOnGround = false;

    auto playerOBB = dynamic_cast<OBB*>(player);
    auto stageOBB = dynamic_cast<OBB*>(stage);

    glm::vec3 gravityDir = world->GetCurrentGravityDir();

    float playerBottom;
    float stageTop;

    //ワールドの回転に応じたOBBの接地判定
    switch (world->GetGravityIndex())
    {
    case 0:
        playerBottom = playerOBB->Center().y - playerOBB->HalfSize().y;
        stageTop     = stageOBB->Center().y + stageOBB->HalfSize().y;
        break;
    case 1:
        playerBottom = playerOBB->Center().x - playerOBB->HalfSize().x;
        stageTop     = stageOBB->Center().x + stageOBB->HalfSize().x;
        break;
    case 2:
        playerBottom = playerOBB->Center().y + playerOBB->HalfSize().y;
        stageTop     = stageOBB->Center().y - stageOBB->HalfSize().y;
        break;
    case 3:
        playerBottom = playerOBB->Center().x + playerOBB->HalfSize().x;
        stageTop     = stageOBB->Center().x - stageOBB->HalfSize().x;
        break;
    
    default:
        break;
    }
    
    // プレイヤーの底面と床の上面との差
    float verticalDistance = playerBottom - stageTop;
    //std::cout << "verticalDistance : ( " << verticalDistance << " )" << std::endl;
    //しきい値
    const float threshold = 0.5f;
    
    //しきい値以内であれば地面の上
    if(verticalDistance > -threshold && verticalDistance < threshold)
    {
        isOnGround = true;
        world->RotateReset();
        //std::cout << "[ON] FLOOR" << std::endl;
    }

    return isOnGround;
}

void Player::FollowMovingFloor()
{
    for (auto s : stage)
    {
        if (!collider->checkCollision(*s->GetCollider())) { continue; }
        //if (!isOnFloor(collider.get(), s->GetCollider())) { continue; }
        if(!CheckGroundByRay()) { return; }

        auto stageOBB = dynamic_cast<OBB*>(s->GetCollider());
        
        // 床の平衡移動量を取得
        glm::vec3 floorMove = stageOBB->Center() - stageOBB->previousCenter;

        //std::cout << "delta : ( " << floorMove.x << ", " << floorMove.y << ", " << floorMove.z << " )" << std::endl;
        // 床の動きに合わせてプレイヤーも動かす
        position += floorMove;

        // 床の回転差を取得
        glm::mat4 currentModel = stageOBB->GetModelMatrix();
        glm::mat4 previousModel = stageOBB->GetPrevModel();

        //回転差分行列の作成
        glm::mat4 rotationDelta = currentModel * glm::inverse(previousModel);

        //プレイヤーの相対位置に回転を適用
        glm::vec3 floorCenter  = stageOBB->Center();
        glm::vec3 offset = position - floorCenter;

        glm::vec3 rotateOffset = glm::vec3(glm::mat3(rotationDelta) * offset);
        position = floorCenter + rotateOffset;
    }
}

void Player::ClearStage()
{
    if(!stage.empty())
    {
        stage.clear();
    }
}


//仮
bool Player::CheckGroundByRay()
{
    auto obb = dynamic_cast<OBB*>(collider.get());
    glm::vec3 center = obb->Center();
    glm::vec3 gravityDir = world->GetCurrentGravityDir();

    // OBBの各軸とサイズ
    glm::vec3 right   = obb->axes[0] * obb->HalfSize().x;
    glm::vec3 forward = obb->axes[2] * obb->HalfSize().z;

    // gravityDirの軸に応じて高さを取得
    float halfHeight = glm::abs(glm::dot(gravityDir, obb->axes[0])) > 0.9f ? obb->HalfSize().x :
                       glm::abs(glm::dot(gravityDir, obb->axes[1])) > 0.9f ? obb->HalfSize().y :
                                                                             obb->HalfSize().z;

    glm::vec3 bottomCenter = center - gravityDir * halfHeight;
    //Helper::printVec3("Player", "obbright", right);
    //Helper::printVec3("Player", "obbforward", forward);
    std::vector<glm::vec3> rayOrigins;
    for (int i = -2; i <= 2; ++i)
    {
        for (int j = -2; j <= 2; ++j)
        {
            glm::vec3 offset = (float)i * right + (float)j * forward;
            rayOrigins.push_back(bottomCenter + offset);
        }
    }

    float rayLength = 0.7f;
    isOnGround = false;

    for (const auto& origin : rayOrigins)
    {
        for (auto s : stage)
        {
            if (s->GetObjectType() == ObjectType::PYRAMID) continue;

            auto stageOBB = dynamic_cast<OBB*>(s->GetCollider());
            float hitDist;

            if (stageOBB->intersectRay(origin, gravityDir, hitDist))
            {
                if (hitDist <= rayLength)
                {
                    isOnGround = true;
                    world->RotateReset();
                    return true;
                }
            }
        }
    }

    return false;
}
