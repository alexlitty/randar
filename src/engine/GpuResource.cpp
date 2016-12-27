#include <randar/engine/GpuResource.hpp>

randar::GpuResource::GpuResource(::GLuint initGlName)
: glName(initGlName)
{

}

randar::GpuResource::~GpuResource()
{

}

randar::GpuResource::operator ::GLuint() const
{
    return this->glName;
}
