#include <randar/render/Camera.hpp>

randar::Camera::Camera()
{
    this->updateMatrices();
}

void randar::Camera::updateMatrices()
{
    // @todo: don't hardcode size
    this->projection = glm::perspective(
        glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f
    );

    this->view = glm::lookAt(
        glm::vec3(this->position.x, this->position.y, this->position.z),
        glm::vec3(this->target.x, this->target.y, this->target.z),
        glm::vec3(0, 1, 0)
    );
}

void randar::Camera::setPosition(randar::Vector newPosition)
{
    this->position = newPosition;
    this->updateMatrices();
}

randar::Vector randar::Camera::getPosition() const
{
    return this->position;
}

void randar::Camera::setTarget(randar::Vector newTarget)
{
    this->target = newTarget;
    this->updateMatrices();
}

randar::Vector randar::Camera::getTarget() const
{
    return this->target;
}

glm::mat4 randar::Camera::getViewMatrix() const
{
    return this->view;
}

glm::mat4 randar::Camera::getProjectionMatrix() const
{
    return this->projection;
}
