#include <randar/render/Joint.hpp>

// @todo - Horribly inefficient. Think of the children!
glm::mat4 randar::Joint::getPoseMatrix() const
{
    if (!this->parent) {
        return this->basePose.getTransformMatrix();
    }
    return this->basePose.getTransformMatrix() * this->parent->getPoseMatrix();
}
