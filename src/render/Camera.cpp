#include <randar/render/Camera.hpp>

randar::Camera::Camera()
: isOrtho(false),
  fieldOfView(45.0f),
  aspectRatio(4.0f / 3.0f),
  nearZ(0.1f),
  farZ(100.0f)
{
    this->updateMatrices();
}

void randar::Camera::onTransform()
{
    this->updateMatrices();
}

void randar::Camera::updateMatrices()
{
    if (this->isOrtho) {
        this->projection = glm::ortho(
            -25.0f,
            25.0f,
            -25.0f,
            25.0f,
            -25.0f,
            25.0f
        );
    } else {
        this->projection = glm::perspective(
            this->fieldOfView.toRadians(),
            this->aspectRatio,
            this->nearZ,
            this->farZ
        );
    }

    this->view = glm::lookAt(
        glm::vec3(this->position.x, this->position.y, this->position.z),
        glm::vec3(this->target.x, this->target.y, this->target.z),

        // @todo - make this based on rotation
        glm::vec3(0, 1, 0)
    );
}

void randar::Camera::setOrtho(bool ortho)
{
    this->isOrtho = ortho;
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
