#ifndef RANDAR_RENDER_MODEL_HPP
#define RANDAR_RENDER_MODEL_HPP

#include <randar/Math/Transformable.hpp>
#include <randar/Render/VertexBuffer.hpp>
#include <randar/Render/IndexBuffer.hpp>

namespace randar
{
    class Model : virtual public GpuResource, virtual public Transformable
    {
        /**
         * The number of mesh textures required to display this model properly.
         */
        uint16_t meshTextureCount = 0;

    public:
        /**
         * Model data.
         */
        std::vector<Vertex> vertices;
        VertexBuffer vertexBuffer;

        std::vector<uint32_t> faceIndices;
        IndexBuffer faceBuffer;

        std::vector<Texture*> meshTextures;
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

        /**
         * Sets and retrievess the number of required mesh textures.
         */
        void setMeshTextureCount(uint16_t newMeshTextureCount);
        uint16_t getMeshTextureCount() const;

        /**
         * Checks whether this model is missing mesh textures.
         */
        bool isMissingMeshTextures() const;

        /**
         * Checks whether this model requires any mesh textures.
         */
        bool requiresMeshTextures() const;
    };
}

#endif
