#ifndef RANDAR_RENDER_INDEX_BUFFER_HPP
#define RANDAR_RENDER_INDEX_BUFFER_HPP

#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct IndexBuffer : virtual public GpuResource
    {
        IndexBuffer();
        IndexBuffer(const IndexBuffer& other);

        unsigned int count;

        virtual void initialize() override;
        virtual void destroy() override;

        IndexBuffer& operator =(const IndexBuffer& other);
    };
}

#endif
