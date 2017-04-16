#include <randar/Render/Camera.hpp>

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
            this->orthoLeft,
            this->orthoRight,
            this->orthoBottom,
            this->orthoTop
        );

        this->view = glm::mat4();
    } else {
        this->projection = glm::perspective(
            this->fieldOfView.toRadians(),
            this->aspectRatio,
            this->nearZ,
            this->farZ
        );

        this->view = glm::lookAt(
            glm::vec3(this->position.x, this->position.y, this->position.z),
            glm::vec3(this->target.x, this->target.y, this->target.z),

            // @todo - make this based on rotation
            glm::vec3(0, 1, 0)
        );
    }
}

void randar::Camera::setOrtho()
{
    this->setOrtho(
        this->viewport.x1,
        this->viewport.x2,
        this->viewport.y2,
        this->viewport.y1
    );
}

void randar::Camera::setOrtho(float left, float right, float bottom, float top)
{
    this->isOrtho = true;
    this->orthoLeft = left;
    this->orthoRight = right;
    this->orthoBottom = bottom;
    this->orthoTop = top;

    this->updateMatrices();
}

void randar::Camera::disableOrtho()
{
    this->isOrtho = false;
    this->updateMatrices();
}

void randar::Camera::setTarget(randar::Vector3 newTarget)
{
    this->target = newTarget;
    this->updateMatrices();
}

randar::Vector3 randar::Camera::getTarget() const
{
    return this->target;
}

void randar::Camera::pan(float x, float y)
{
    Vector3 movement(x, y);

    this->move(movement);
    this->target += movement;

    this->updateMatrices();
}

glm::mat4 randar::Camera::getViewMatrix() const
{
    return this->view;
}

glm::mat4 randar::Camera::getProjectionMatrix() const
{
    return this->projection;
}
