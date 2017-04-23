#include <randar/Engine/GpuResource.hpp>

// Constructors and destructor.
randar::GpuResource::GpuResource(randar::GraphicsContext& initCtx)
: ctx(&initCtx),
  glName(0)
{

}

randar::GpuResource::GpuResource(randar::Gpu* initGpu)
: gpu(initGpu),
  glName(0)
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
