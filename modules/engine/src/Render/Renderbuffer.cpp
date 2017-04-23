#include <randar/Render/Renderbuffer.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructor.
randar::Renderbuffer::Renderbuffer(
    randar::GraphicsContext& context,
    unsigned int initWidth,
    unsigned int initHeight,
    const std::string& initType)
: randar::GpuResource(context),
  bufferType(initBufferType),
  width(initWidth),
  height(initHeight)
{
    if (this->gpu) {
        this->gpu->initialize(*this);
    }
}

// Constructs a new renderbuffer from an existing one.
randar::Renderbuffer::Renderbuffer(const randar::Renderbuffer& other)
: type(other.type),
  width(other.width),
  height(other.height)
{
    if (this->gpu) {
        this->gpu->initialize(*this);
    }
}

// Destructor.
randar::Renderbuffer::~Renderbuffer()
{
    if (this->gpu) {
        this->gpu->destroy(*this);
    }
}

// Resizes this framebuffer.
void randar::Renderbuffer::resize(unsigned int width, unsigned int height)
{
    if (this->gpu) {
        this->gpu->resize(*this, width, height);
    }
}
