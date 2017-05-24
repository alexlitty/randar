#include <randar/Render/Joint.hpp>

// @todo - Horribly inefficient. Think of the children!
glm::mat4 randar::Joint::getPoseMatrix() const
{
    if (!this->parent) {
        return this->transformMatrix();
    }
    return this->transformMatrix() * this->parent->getPoseMatrix();
}
