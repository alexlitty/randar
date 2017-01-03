#ifndef RANDAR_RENDER_MESH_HPP
#define RANDAR_RENDER_MESH_HPP

#include <randar/Engine/AggregateResource.hpp>

namespace randar
{
    struct Mesh : virtual public AggregateResource
    {
        /**
         * Resource information.
         */
        const static Resource::Type type;
        Resource::Type getType() const;

        /**
         * Mesh information.
         */
        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;

        /**
         * Resource initialization and destruction.
         */
        virtual void initialize(Gpu& gpu) override;
        virtual void destroy(Gpu& gpu) override;
    };
}

#endif
