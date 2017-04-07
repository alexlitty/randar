#ifndef RANDAR_RENDER_INDEX_BUFFER_HPP
#define RANDAR_RENDER_INDEX_BUFFER_HPP

#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct IndexBuffer : virtual public GpuResource
    {
        unsigned int count;

        virtual void initialize() override;
        virtual void destroy() override;
    };
}

#endif
