#include <randar/Render/Camera.hpp>

randar::Camera::Camera()
{

}

void randar::Camera::updateMatrices() const
{
    switch (this->type) {
        case CameraType::ORTHO:
            this->proj = glm::ortho(
                this->orthoLeft,
                this->orthoRight,
                this->orthoBottom,
                this->orthoTop,
                this->nearZ,
                this->farZ
            );

            //this->view = glm::mat4();
            this->view = glm::lookAt(
                glm::vec3(this->position().x, this->position().y, this->position().z),
                glm::vec3(this->targ.x, this->targ.y, this->targ.z),

                // @todo - make this based on rotation
                glm::vec3(0, 1, 0)
            );
            break;

        case CameraType::PROJECTION:
            this->proj = glm::perspective(
                this->fov.toRadians(),
                this->aspectRatio,
                this->nearZ,
                this->farZ
            );

            this->view = glm::lookAt(
                glm::vec3(this->position().x, this->position().y, this->position().z),
                glm::vec3(this->targ.x, this->targ.y, this->targ.z),

                // @todo - make this based on rotation
                glm::vec3(0, 1, 0)
            );
            break;

        default:
            this->proj = glm::mat4();
            this->view = glm::mat4();
            break;
    }
}

void randar::Camera::ortho()
{
    this->ortho(
        this->viewport.x1,
        this->viewport.x2,
        this->viewport.y2,
        this->viewport.y1
    );
}

void randar::Camera::ortho(float left, float right, float bottom, float top)
{
    this->type = CameraType::ORTHO;

    this->orthoLeft = left;
    this->orthoRight = right;
    this->orthoBottom = bottom;
    this->orthoTop = top;
}

void randar::Camera::projection()
{
    this->type = CameraType::PROJECTION;
}

void randar::Camera::target(randar::Vector3 newTarget)
{
    this->targ = newTarget;
}

randar::Vector3 randar::Camera::target() const
{
    return this->targ;
}

void randar::Camera::pan(float x, float y)
{
    Vector3 movement(x, y);

    this->move(movement);
    this->targ += movement;
}

// Sets the near and far Z.
void randar::Camera::range(float newNearZ, float newFarZ)
{
    this->nearZ = newNearZ;
    this->farZ  = newFarZ;
}

glm::mat4 randar::Camera::viewMatrix() const
{
    this->updateMatrices();
    return this->view;
}

glm::mat4 randar::Camera::projectionMatrix() const
{
    this->updateMatrices();
    return this->proj;
}
