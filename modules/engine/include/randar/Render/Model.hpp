#ifndef RANDAR_RENDER_MODEL_HPP
#define RANDAR_RENDER_MODEL_HPP

#include <randar/Math/Transform.hpp>
#include <randar/Render/VertexBuffer.hpp>
#include <randar/Render/IndexBuffer.hpp>

namespace randar
{
    class Model : virtual public GpuResource, virtual public Transform
    {
        bool dirty = false;

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
         */
        Model(Gpu* gpuInit = nullptr);

        /**
         * Destructor.
         */
        ~Model();

        /**
         * Whether this model is initialized on the GPU.
         */
        bool isInitialized() const;

        /**
         * Checks whether this model is missing mesh textures.
         */
        bool isMissingMeshTextures() const;

        /**
         * Sets a mesh texture.
         */
        void setMeshTexture(uint32_t slotId, Texture* texture);

        /**
         * Whether this model has changed since last being saved.
         */
        bool isDirty() const;

        /**
         * Retrieves model metadata as JSON.
         */
        Json toJson() const;
    };
}

#endif
