#include "Behavior/Behavior.h"
#include "GLHeaders.h"
#include <iostream>
#include <cmath>

RotateBehavior::RotateBehavior(glm::vec3 axis_, float speed_)
:axis(axis_), speed(speed_) { }

void RotateBehavior::Update(Transform& transform, float deltaTime)
{
    transform.rotation += axis * speed * deltaTime;
}

RoundBehavior::RoundBehavior(glm::vec3 axis_, float val_)
:axis(axis_), val(val_) 
{

}
void RoundBehavior::Update(Transform& transform, float deltaTime)
{
    glm::vec3 delta( 
        axis.x * sin(glfwGetTime()) * val,
        axis.y * sin(glfwGetTime()) * val,
        axis.z * sin(glfwGetTime()) * val
    );
    //std::cout << "Round : ( " << delta.x << ", " << delta.y << ", " << delta.z << " )" << std::endl;
    transform.position += delta;
}

TranslateBehavior::TranslateBehavior(glm::vec3 trans_, float val_)
:translate(trans_), val(val_) 
{

}
void TranslateBehavior::Update(Transform& transform, float deltaTime)
{

}


ScaledBehavior::ScaledBehavior(glm::vec3 scale_, float val_)
:scale(scale_), val(val_)
{

}
void ScaledBehavior::Update(Transform& transform, float deltaTimemodel)
{

}

void CompositeBehavior::addBehavior(std::unique_ptr<Behavior> behavior)
{
    behaviors.push_back(std::move(behavior));
}

void CompositeBehavior::Update(Transform& transform, float deltaTime)
{
    for(auto& b : behaviors)
    {
        b->Update(transform, deltaTime);
    }
}