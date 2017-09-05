#include <randar/Render/Model.hpp>

// Constructors.
randar::Model::Model()
: geo(nullptr),
  program(nullptr),
  skel(nullptr)
{

}

// Assignment.
randar::Model::Model(const randar::Model& other)
: randar::Model::Model()
{
    *this = other;
}

randar::Model& randar::Model::operator =(const randar::Model& other)
{
    this->geo = other.geo;
    this->program = other.program;

    this->position(other.position());
    this->rotation(other.rotation());

    return *this;
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

// Sets and retrieves the skeleton applied to the model.
void randar::Model::skeleton(randar::Skeleton& skeleton)
{
    this->skel = &skeleton;
}

randar::Skeleton& randar::Model::skeleton()
{
    if (!this->hasSkeleton()) {
        throw std::runtime_error("Model has no skeleton");
    }
    return *this->skel;
}

bool randar::Model::hasSkeleton() const
{
    return this->skel != nullptr;
}

// Node.js helper for intuitive model creation.
randar::Model randar::model()
{
    return randar::Model();
}
