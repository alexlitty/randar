#include <randar/Render/Model.hpp>

// Constructors.
randar::Model::Model()
{

}

// Destructor.
randar::Model::~Model()
{

}

// Sets and retrieves the model geometry.
void randar::Model::geometry(randar::Geometry& newGeometry)
{
    this->geo = &newGeometry;
}

randar::Geometry& randar::Model::geometry()
{
    if (!this->hasGeometry()) {
        throw std::runtime_error("Model has no geometry assigned");
    }
    return *this->geo;
}

bool randar::Model::hasGeometry() const
{
    return this->geo != nullptr;
}

// Sets and retrieves the shader program used by the model.
void randar::Model::shaderProgram(randar::ShaderProgram& newProgram)
{
    this->program = &newProgram;
}

randar::ShaderProgram& randar::Model::shaderProgram()
{
    if (!this->hasShaderProgram()) {
        throw std::runtime_error("Model has no shader program assigned");
    }
    return *this->program;
}

bool randar::Model::hasShaderProgram() const
{
    return this->program != nullptr;
}

// Draws the geometry to a framebuffer.
void randar::Model::drawTo(randar::Framebuffer& fb)
{
    if (!this->hasGeometry()) {
        throw std::runtime_error("Cannot draw model without geometry");
    }

    ShaderProgram* drawProgram = this->program;
    if (!drawProgram) {
        drawProgram = &fb.context().defaultShaderProgram();
    }

    fb.draw(this->geometry(), *this, *drawProgram);
}
