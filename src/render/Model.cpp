#include <randar/render/Model.hpp>

randar::Model::~Model()
{
    for (auto joint : this->joints) {
        delete joint;
    }
}

void randar::Model::draw() const
{
    if (!this->shaderProgram) {
        throw std::runtime_error("Cannot draw without shader program");
    }

    glm::mat4 jointMatrices[this->joints.size()];
    for (unsigned int i = 0; i < this->joints.size(); i++) {
        jointMatrices[i] = this->joints[i]->getPoseMatrix();
    }

    // @todo - Modernize
    ::glUniformMatrix4fv(
        ::glGetUniformLocation(this->shaderProgram->getGlName(), "joints"),
        this->joints.size(),
        GL_FALSE,
        &jointMatrices[0][0][0]
    );
    this->mesh.draw();
}
