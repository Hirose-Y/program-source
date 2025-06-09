#include "Math/Ray.h"
#include "Core/GLHeaders.h"

Ray::Ray()
:origin(glm::vec3(0.0f)), direction(glm::vec3(0.0f))
{

}

Ray::Ray(const glm::vec3& origin_, const glm::vec3& direction_)
:origin(origin_), direction(glm::normalize(direction_))
{

}