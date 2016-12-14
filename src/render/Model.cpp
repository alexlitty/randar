#include <randar/render/Model.hpp>

void randar::Model::draw() const
{
    glm::mat3x4 jointMatrices[this->joints.size()];
    for (unsigned int i = 0; i < this->joints.size(); i++) {
        jointMatrices[i] = randar::toMat3x4(this->joints[i].getTransformMatrix());
    }
    this->mesh.draw();
}
