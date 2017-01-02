#ifndef RANDAR_RENDER_RENDERBUFFER_HPP
#define RANDAR_RENDER_RENDERBUFFER_HPP

#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct Renderbuffer : virtual public GpuResource
    {
        const static Resource::Type type;
        Resource::Type getType() const;
    };
}

#endif
