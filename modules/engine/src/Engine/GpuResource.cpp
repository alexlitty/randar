#include <randar/Engine/GpuResource.hpp>

// Constructor and destructor.
randar::GpuResource::GpuResource()
: glName(0)
{

}

randar::GpuResource::~GpuResource()
{

}

// Whether this resource is initialized on the GPU.
bool randar::GpuResource::isInitialized() const
{
    return this->glName != 0;
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
