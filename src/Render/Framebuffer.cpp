#include <randar/Render/Framebuffer.hpp>

const randar::Resource::Type randar::Framebuffer::type = randar::Resource::FRAMEBUFFER;
randar::Resource::Type randar::Framebuffer::getType() const
{
    return this->type;
}

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
