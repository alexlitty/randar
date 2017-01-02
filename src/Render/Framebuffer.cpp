#include <randar/Render/Framebuffer.hpp>

randar::Framebuffer::Framebuffer(const Viewport& initViewport)
{
    this->camera.viewport = initViewport;
}
