#include <randar/Render/Framebuffer.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructor.
randar::Framebuffer::Framebuffer(
    unsigned int width,
    unsigned int height,
    randar::Texture::Type textureType,
    bool enableDepthBuffer)
: depthBufferEnabled(enableDepthBuffer),
  texture(textureType, width, height),
  depthBuffer(randar::Renderbuffer::DEPTH, width, height)
{
    this->camera.viewport = Viewport(0, 0, width, height);
}

// Checks whether a depth buffer is enabled.
bool randar::Framebuffer::hasDepthBuffer() const
{
    return this->depthBufferEnabled;
}

// Initialize this framebuffer.
void randar::Framebuffer::initialize(randar::Gpu& gpu)
{
    gpu.initialize(*this);
    this->initialized = true;
}

// Destroys this framebuffer.
void randar::Framebuffer::destroy(randar::Gpu& gpu)
{
    gpu.destroy(*this);
    this->initialized = false;
}
