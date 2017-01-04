#ifndef RANDAR_RENDER_INDEX_BUFFER_HPP
#define RANDAR_RENDER_INDEX_BUFFER_HPP

#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct IndexBuffer : virtual public GpuResource
    {
        virtual void initialize(Gpu& gpu) override;
        virtual void destroy(Gpu& gpu) override;
    };
}

#endif
