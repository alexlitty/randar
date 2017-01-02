#include <randar/Engine/GpuResource.hpp>

// Constructor and destructor.
randar::GpuResource::GpuResource()
{

}

randar::GpuResource::~GpuResource()
{

}

// OpenGL name assignment and retrieval.
void randar::GpuResource::setGlName(::GLuint newGlName)
{
    this->glName = newGlName;
}

::GLuint randar::GpuResource::getGlName() const
{
    return this->glName;
}

randar::GpuResource::operator ::GLuint() const
{
    return this->getGlName();
}

randar::GpuResource::operator ::GLuint*()
{
    return &this->glName;
}

randar::GpuResource::operator ::GLuint&()
{
    return this->glName;
}
