#ifndef RANDAR_RENDER_MODEL_HPP
#define RANDAR_RENDER_MODEL_HPP

#include <randar/Math/Transformable.hpp>
#include <randar/Engine/FileResource.hpp>
#include <randar/Render/VertexBuffer.hpp>
#include <randar/Render/IndexBuffer.hpp>

namespace randar
{
    class Model : virtual public FileResource, virtual public Transformable
    {
        /**
         * Serialization helpers.
         */
        uint32_t vertexCount;
        uint32_t faceCount;
        uint8_t textureCount;
        uint32_t jointCount;
        uint32_t jointWeightCount;

    public:
        /**
         * Model data.
         */
        std::vector<Vertex> vertices;
        VertexBuffer vertexBuffer;

        std::vector<uint32_t> faceIndices;
        IndexBuffer faceBuffer;

        std::map<uint32_t, Texture*> textures;
        std::vector<Joint*> joints;

        /**
         * Constructs a new model.
         *
         * Must be manually initialized on the GPU.
         */
        Model();

        /**
         * Destructor.
         */
        ~Model();
    };
}

#endif
