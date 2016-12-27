#ifndef RANDAR_RENDER_FRAMEBUFFER_HPP
#define RANDAR_RENDER_FRAMEBUFFER_HPP

#include <randar/engine/GpuResource.hpp>

namespace randar
{
    class Framebuffer : virtual public GpuResource
    {
    public:
        Framebuffer(::GLuint initGlName);
    };
}

#endif
