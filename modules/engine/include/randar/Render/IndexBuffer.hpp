#ifndef RANDAR_RENDER_INDEX_BUFFER_HPP
#define RANDAR_RENDER_INDEX_BUFFER_HPP

#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct IndexBuffer : virtual public GpuResource
    {
        IndexBuffer(Gpu& initGpu);
        IndexBuffer(const IndexBuffer& other);

        unsigned int count;

        IndexBuffer& operator =(const IndexBuffer& other);
    };
}

#endif
