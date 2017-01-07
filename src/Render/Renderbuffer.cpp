#include <randar/Render/Renderbuffer.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructor.
randar::Renderbuffer::Renderbuffer(randar::Renderbuffer::Type initType, unsigned int initWidth, unsigned int initHeight)
: type(initType),
  width(initWidth),
  height(initHeight)
{

}

// Resizes this framebuffer.
void randar::Renderbuffer::resize(unsigned int width, unsigned int height)
{
    this->gpu.resize(*this, width, height);
}

// Resource initialization.
void randar::Renderbuffer::initialize()
{
    this->gpu.initialize(*this);
    this->initialized = true;
}

// Resource destruction.
void randar::Renderbuffer::destroy()
{
    this->gpu.destroy(*this);
    this->initialized = false;
}
