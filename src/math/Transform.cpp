#include <randar/math/Transform.hpp>

glm::mat4 randar::Transform::getMatrix() const
{
    return this->getTransformMatrix();
}
