#include "Core/GLHeaders.h"
#include "Object/ObjectInfo.h"
#include "Object/Object_Pyramid.h"
#include "Collider/Collider_OBB.h"
#include "Collider/ColliderType.h"
#include "Camera/Camera.h"
#include "Graphics/Light.h"
#include "World/World.h"
#include "Graphics/Shader.h"

#include <iostream>
#include <vector>
#include <cmath>

Pyramid::Pyramid(Shader* shaderProgram, World* world_, ObjectInfo info_, std::unique_ptr<Behavior> behavior) 
: Object("Assets/obj/pyramid.obj")
,info(info_), world(world_), shader(shaderProgram), movebehavior(std::move(behavior))
{
    isdraw = true;
    Initialize();
}

Pyramid::~Pyramid()
{

}

void Pyramid::Initialize()
{
    info.transparency = 1.0f;
    modelMatrix = info.transform.getModelMatrix();

    previousmodelMatrix = modelMatrix;
    collider = std::make_unique<OBB>(modelMatrix);
}

void Pyramid::Update(float deltaTime)
{
    if(world->isWorldRotation()) return;
    
    previousmodelMatrix = modelMatrix;
    
    movebehavior->Update(info.transform, deltaTime);
    modelMatrix = info.transform.getModelMatrix();

    collider->Update(modelMatrix);
}

void Pyramid::draw(Camera* camera, Light* light)
{    
    if(!isdraw) { return; }

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

    // オブジェクトの色・透明度
    shader->SetVec3("objectColor", info.color);
    shader->SetFloat("transparency", info.transparency);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3); // 描画
    glBindVertexArray(0);
}
