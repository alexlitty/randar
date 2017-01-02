#ifndef RANDAR_RENDER_MESH_HPP
#define RANDAR_RENDER_MESH_HPP

#include <randar/Render/IndexBuffer.hpp>
#include <randar/Render/VertexBuffer.hpp>

namespace randar
{
    struct Mesh
    {
        IndexBuffer indexBuffer;
        VertexBuffer vertexBuffer;
    };
}

#endif
