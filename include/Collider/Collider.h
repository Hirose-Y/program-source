#ifndef COLLIDER_H
#define COLLIDER_H

#include "GLHeaders.h"
#include "Object/Object.h"
#include "Collider/ColliderType.h"

class Collider
{
public:
    virtual void Update(const glm::mat4 model) = 0;

    virtual bool checkCollision(const Collider& other) const = 0;
    virtual glm::vec3 resolveCollision(const Collider& other) = 0;

    virtual ColliderType getType() const = 0;
    virtual ~Collider() = default;
};

#endif /* COLLIDER_H */