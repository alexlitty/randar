#include <randar/render/Transform.hpp>

void randar::Transform::updateMatrix()
{
    this->matrix = glm::mat4(1.0f);
}

randar::Transform::Transform()
{
    this->updateMatrix();
}

void randar::Transform::setPosition(Vector newPosition)
{
    this->position = newPosition;
    this->updateMatrix();
}

void randar::Transform::move(Vector relativePosition)
{
    this->position.x += relativePosition.x;
    this->position.y += relativePosition.y;
    this->position.z += relativePosition.z;
    this->updateMatrix();
}

glm::mat4 randar::Transform::getMatrix() const
{
    return this->matrix;
}
