#ifndef RANDAR_RENDER_MESH_HPP
#define RANDAR_RENDER_MESH_HPP

#include <randar/Engine/FileResource.hpp>
#include <randar/Render/VertexBuffer.hpp>
#include <randar/Render/IndexBuffer.hpp>

namespace randar
{
    struct Mesh : virtual public FileResource
    {
        /**
         * Mesh information.
         */
        uint32_t vertexCount;
        uint32_t faceCount;
        uint8_t textureCount;
        uint32_t jointCount;
        uint32_t jointWeightCount;

        /**
         * Mesh data.
         */
        std::vector<Vertex> vertices;
        VertexBuffer vertexBuffer;

        std::vector<uint32_t> faceIndices;
        IndexBuffer faceBuffer;

        std::vector<Texture*> textures;
        std::vector<Joint*> joints;

        /**
         * Constructs a new mesh.
         */
        Mesh();

        /**
         * Constructs an existing mesh from a file.
         */
        Mesh(const std::string& file);

        /**
         * Destructor.
         */
        ~Mesh();

        /**
         * Saves this mesh to its file.
         */
        virtual bool save() override;
    };
}

#endif
