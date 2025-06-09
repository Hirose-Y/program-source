#ifndef RAY_H
#define RAY_H

#include "Core/GLHeaders.h"

class Ray
{
public:
    Ray();
    Ray(const glm::vec3& origin_, const glm::vec3& direction_);

    const glm::vec3& GetOrigin() const { return origin; }
    const glm::vec3& GetDirection() const { return direction; }

    glm::vec3 GetPoint(float t) const { return origin + t * direction; }
private:
    glm::vec3 origin;
    glm::vec3 direction;
};

#endif /* RAY_H */