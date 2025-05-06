#include "GLHeaders.h"
#include "Collider/Collider_AABB.h"
#include "Collider/Collider_OBB.h"

#include <iostream>

AABB::AABB(const glm::mat4 model)
{
    bool success = glm::decompose(model, extractedScale, orientation, extractedTranslation, skew, perspective);
    if (success) {
        halfSize = glm::vec3(extractedScale.x / 2, extractedScale.y / 2, extractedScale.z / 2);
        center = extractedTranslation;
    }
}

void AABB::Update(const glm::mat4 model)
{
    bool success = glm::decompose(model, extractedScale, orientation, extractedTranslation, skew, perspective);
    if (success) {
        halfSize = glm::vec3(extractedScale.x / 2, extractedScale.y / 2, extractedScale.z / 2);
        center = extractedTranslation;
    }
}
    

bool AABB::checkCollision(const Collider& other) const
{
    if (other.getType() == ColliderType::AABB) {
        const AABB& otherAABB = static_cast<const AABB&>(other);

        if(!( center.x + halfSize.x < otherAABB.center.x - otherAABB.halfSize.x ||
              center.x - halfSize.x > otherAABB.center.x + otherAABB.halfSize.x ||
              center.y + halfSize.y < otherAABB.center.y - otherAABB.halfSize.y ||
              center.y - halfSize.y > otherAABB.center.y + otherAABB.halfSize.y ||
              center.z + halfSize.z < otherAABB.center.z - otherAABB.halfSize.z ||
              center.z - halfSize.z > otherAABB.center.z + otherAABB.halfSize.z ))
        {
            #ifdef DEBUG_MODE
            std::cout << "<Collision> AABB" << std::endl;
            #endif
            return true;
        }
    } 
    
    return false;
}

glm::vec3 AABB::resolveCollision(const Collider& other)
{
    return glm::vec3(0.0f);
}

