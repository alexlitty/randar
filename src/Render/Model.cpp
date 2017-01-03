#include <randar/Render/Model.hpp>

randar::Model::~Model()
{
    for (auto joint : this->joints) {
        delete joint;
    }
}

const randar::ShaderProgram& randar::Model::getShaderProgram() const
{
    return this->shaderProgram;
}
