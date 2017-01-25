#include <randar/Render/Framebuffer.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructor.
randar::Framebuffer::Framebuffer(
    std::string textureType,
    bool enableDepthBuffer,
    unsigned int width,
    unsigned int height)
: depthBufferEnabled(enableDepthBuffer),
  texture(textureType, width, height),
  depthBuffer(randar::Renderbuffer::DEPTH, width, height)
{
    this->camera.viewport = Viewport(0, 0, width, height);
    this->gpu.initialize(*this);
}

// Destructor.
randar::Framebuffer::~Framebuffer()
{
    // Don't destroy the default framebuffer.
    if (this->getGlName() != 0) {
        this->gpu.destroy(*this);
    }
}

// Whether this framebuffer is initialized on the GPU.
bool randar::Framebuffer::isInitialized() const
{
    return true;
}

// Checks whether a depth buffer is enabled.
bool randar::Framebuffer::hasDepthBuffer() const
{
    return this->depthBufferEnabled;
}

// Resizes this framebuffer and its dependencies.
void randar::Framebuffer::resize(unsigned int width, unsigned int height)
{
    this->gpu.resize(*this, width, height);
}
