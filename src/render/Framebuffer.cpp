#include <randar/render/Framebuffer.hpp>

randar::Framebuffer::Framebuffer(::GLuint initGlName, const Viewport& initViewport)
: randar::GpuResource(initGlName)
{
    this->camera.viewport = initViewport;
}
