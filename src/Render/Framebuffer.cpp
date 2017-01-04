#include <randar/Render/Framebuffer.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructs a framebuffer with no attachments.
randar::Framebuffer::Framebuffer(const Viewport& initViewport)
: texture(nullptr)
{
    this->camera.viewport = initViewport;
}

// Constructs a framebuffer with a single texture attachment.
randar::Framebuffer::Framebuffer(randar::Texture* initTexture)
: texture(initTexture)
{
    this->camera.viewport = Viewport(0, 0, initTexture->width, initTexture->height);
}

// Retrieves the texture attachment.
randar::Texture* randar::Framebuffer::getTexture()
{
    return this->texture;
}

// Initialize this framebuffer.
void randar::Framebuffer::initialize(randar::Gpu& gpu)
{
    gpu.initialize(*this);
}

// Destroys this framebuffer.
void randar::Framebuffer::destroy(randar::Gpu& gpu)
{
    gpu.destroy(*this);
}
