#ifndef RANDAR_RENDER_VERTEX_BUFFER_HPP
#define RANDAR_RENDER_VERTEX_BUFFER_HPP

#include <randar/Render/GlBuffer.hpp>
#include <randar/Render/Vertex.hpp>

namespace randar
{
    /**
     * A high-level buffer of vertices.
     */
    class VertexBuffer : virtual public GraphicsContextResource
    {
    protected:
        /**
         * Redundant list of vertices in this vertex buffer.
         *
         * Used to optimize certain operations.
         */
        std::vector<Vertex> vertices;

        /**
         * OpenGL vertex array object, which acts as a container for "attribute"
         * buffers.
         *
         * Simplifies and optimizes rendering operations.
         */
        GLuint vertexArrayName;

        /**
         * OpenGL buffers, each holding a specific vertex attribute for all
         * vertices in this "vertex buffer."
         *
         * These buffers hold the final data used during rendering operations.
         */
        FloatArrayBuffer positionBuffer;
        FloatArrayBuffer colorBuffer;
        FloatArrayBuffer normalBuffer;

        ShortArrayBuffer textureIdBuffer;
        FloatArrayBuffer textureCoordinateBuffer;

        UShortArrayBuffer jointIndexBuffer;
        UCharArrayBuffer jointWeightBuffer;

    public:
        /**
         * Constructors.
         */
        VertexBuffer();
        VertexBuffer(GraphicsContext& context);

        /**
         * Assignment.
         */
        VertexBuffer(const VertexBuffer& other);
        VertexBuffer& operator =(const VertexBuffer& other);

        /**
         * Destructor.
         *
         * Uninitializes the vertex buffer if initialized.
         */
        ~VertexBuffer();

        /**
         * Initializes the vertex buffer on a context.
         *
         * Nothing happens if already initialized. Throws an exception if
         * initialization fails.
         */
        using GraphicsContextResource::initialize;
        virtual void initialize() override;

        /**
         * Uninitializes the vertex buffer from a context.
         *
         * Nothing happens if not initialized. Never throws an exception.
         */
        virtual void uninitialize() override;

        /**
         * Whether the vertex buffer is initialized on a context.
         */
        bool isInitialized() const;

        /**
         * Binds the vertex buffer for further operations.
         *
         * Technically, this only binds the OpenGL vertex array since it is the
         * only binding required for "vertex buffer" operations.
         */
        void bind();

        /**
         * Syncs local data to the OpenGL buffers.
         */
        void sync();

        /**
         * Clears the vertex buffer.
         */
        void clear();

        /**
         * Appends a new vertex.
         */
        void append(const Vertex& vertex);

        /**
         * Retrieves the vertex at the desired index.
         *
         * This is quite inefficient. Made available for debugging and testing.
         *
         * Throws an exception if the index exceeds the buffer size.
         */
        Vertex get(uint32_t index) const;

        /**
         * Queries the vertex at the desired index in the lower level buffers.
         *
         * This is extremely inefficient. Made available for debugging and
         * testing. You will never need to use this for practical purposes.
         *
         * Does not perform syncing prior to querying. Does not perform any
         * out-of-range checks.
         */
        Vertex query(uint32_t index);

        /**
         * Whether this collection contains a vertex.
         */
        bool has(const Vertex& vertex) const;

        /**
         * Finds the index of a vertex in this collection.
         *
         * Returns true if the vertex was found, false otherwise. The index
         * parameter is filled with the found vertex, or remains unchanged if
         * the vertex wasn't found.
         */
        bool find(const Vertex& vertex, uint32_t& index);

        /**
         * Finds the index of a vertex in this collection.
         *
         * Throws an exception if the vertex cannot be found.
         */
        uint32_t find(const Vertex& vertex);

        /**
         * Counts the vertices in this collection.
         */
        uint32_t count() const;
    };
}

#endif
