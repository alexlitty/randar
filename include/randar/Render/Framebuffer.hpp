#ifndef RANDAR_RENDER_FRAMEBUFFER_HPP
#define RANDAR_RENDER_FRAMEBUFFER_HPP

#include <randar/Engine/GpuResource.hpp>
#include <randar/Render/Camera.hpp>

namespace randar
{
    class Framebuffer : virtual public GpuResource
    {
    public:
        Camera camera;
        Framebuffer(const Viewport& initViewport = Viewport(0, 0, 1, 1));
    };
}

#endif
