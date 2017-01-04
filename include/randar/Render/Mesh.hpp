#ifndef RANDAR_RENDER_MESH_HPP
#define RANDAR_RENDER_MESH_HPP

#include <randar/Render/VertexBuffer.hpp>
#include <randar/Render/IndexBuffer.hpp>

namespace randar
{
    struct Mesh : virtual public Resource
    {
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
