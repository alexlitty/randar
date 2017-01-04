#ifndef RANDAR_RENDER_RENDERBUFFER_HPP
#define RANDAR_RENDER_RENDERBUFFER_HPP

#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct Renderbuffer : virtual public GpuResource
    {
        virtual void initialize(Gpu& gpu) override;
        virtual void destroy(Gpu& gpu) override;
    };
}

#endif
