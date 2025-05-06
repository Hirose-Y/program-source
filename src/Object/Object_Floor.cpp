#include "GLHeaders.h"
#include "Object/ObjectInfo.h"
#include "Object/Object_Floor.h"
#include "Collider/Collider_OBB.h"
#include "Collider/ColliderType.h"
#include "Camera/Camera.h"
#include "Light.h"
#include "World/World.h"
#include "Shader.h"

#include <iostream>

Floor::Floor(Shader* shaderProgram, World* world_, ObjectInfo info_, std::unique_ptr<Behavior> behavior) 
:Object("Assets/obj/cube.obj")
,info(info_), world(world_), shader(shaderProgram), movebehavior(std::move(behavior))
{
    Initialize();
}

Floor::~Floor()
{

}

void Floor::Initialize()
{
    modelMatrix = info.transform.getModelMatrix();     
    
    collider = std::make_unique<OBB>(modelMatrix);
}

void Floor::Update(float deltaTime)
{
    if(world->isWorldRotation()) return;
    
    previousmodelMatrix = modelMatrix;

    movebehavior->Update(info.transform, deltaTime);
    modelMatrix = info.transform.getModelMatrix();


    collider->Update(modelMatrix);
}

void Floor::draw(Camera* camera, Light* light)
{
    auto view = world->GetWorldRotation() * camera->getViewMatrix();
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
    shader->SetVec3("objectColor", info.color);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3); // 描画
    glBindVertexArray(0);
}
