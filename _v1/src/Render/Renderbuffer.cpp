#include <randar/Render/Renderbuffer.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructor.
randar::Renderbuffer::Renderbuffer(randar::Renderbuffer::Type initType, unsigned int initWidth, unsigned int initHeight)
: type(initType),
  width(initWidth),
  height(initHeight)
{
    this->gpu.initialize(*this);
}

// Constructs a new renderbuffer from an existing one.
randar::Renderbuffer::Renderbuffer(const randar::Renderbuffer& other)
: type(other.type),
  width(other.width),
  height(other.height)
{
    this->gpu.initialize(*this);
}

// Destructor.
randar::Renderbuffer::~Renderbuffer()
{
    this->gpu.destroy(*this);
}

// Resizes this framebuffer.
void randar::Renderbuffer::resize(unsigned int width, unsigned int height)
{
    this->gpu.resize(*this, width, height);
}
