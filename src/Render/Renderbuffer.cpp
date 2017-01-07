#include <randar/Render/Renderbuffer.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructor.
randar::Renderbuffer::Renderbuffer(randar::Renderbuffer::Type initType, unsigned int initWidth, unsigned int initHeight)
: type(initType),
  width(initWidth),
  height(initHeight)
{

}

// Resource initialization.
void randar::Renderbuffer::initialize(randar::Gpu& gpu)
{
    gpu.initialize(*this);
    this->initialized = true;
}

// Resource destruction.
void randar::Renderbuffer::destroy(randar::Gpu& gpu)
{
    gpu.destroy(*this);
    this->initialized = false;
}
