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

// Resizes this framebuffer and its dependencies.
void randar::Framebuffer::resize(unsigned int width, unsigned int height)
{
    this->camera.viewport = Viewport(0, 0, width, height);
    this->texture.resize(width, height);

    if (this->hasDepthBuffer()) {
        this->depthBuffer.resize(width, height);
    }
}

// Initialize this framebuffer.
void randar::Framebuffer::initialize()
{
    this->gpu.initialize(*this);
    this->initialized = true;
}

// Destroys this framebuffer.
void randar::Framebuffer::destroy()
{
    this->gpu.destroy(*this);
    this->initialized = false;
}
