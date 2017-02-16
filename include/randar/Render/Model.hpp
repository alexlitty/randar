#ifndef RANDAR_RENDER_MODEL_HPP
#define RANDAR_RENDER_MODEL_HPP

#include <randar/Math/Transformable.hpp>
#include <randar/Render/VertexBuffer.hpp>
#include <randar/Render/IndexBuffer.hpp>

namespace randar
{
    class Model : virtual public GpuResource, virtual public Transformable
    {
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
         * Retrieves model metadata as JSON.
         */
        Json toJson() const;
    };
}

#endif
