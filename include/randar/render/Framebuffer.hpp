#ifndef RANDAR_RENDER_FRAMEBUFFER_HPP
#define RANDAR_RENDER_FRAMEBUFFER_HPP

#include <randar/engine/GpuResource.hpp>
#include <randar/render/Camera.hpp>

namespace randar
{
    class Framebuffer : virtual public GpuResource
    {
    public:
        Camera camera;
        Framebuffer(::GLuint initGlName, const Viewport& initViewport = Viewport(0, 0, 1, 1));
    };
}

#endif
