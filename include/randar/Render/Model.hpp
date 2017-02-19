#ifndef RANDAR_RENDER_MODEL_HPP
#define RANDAR_RENDER_MODEL_HPP

#include <randar/Math/Transformable.hpp>
#include <randar/Render/VertexBuffer.hpp>
#include <randar/Render/IndexBuffer.hpp>

namespace randar
{
    class Model : virtual public GpuResource, virtual public Transformable
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
         *
         * Must be manually initialized on the GPU.
         */
        Model();

        /**
         * Destructor.
         */
        ~Model();

        /**
         * Whether this model is initialized on the GPU.
         */
        virtual bool isInitialized() const override;

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
