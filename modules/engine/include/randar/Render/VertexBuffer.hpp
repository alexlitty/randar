#ifndef RANDAR_RENDER_VERTEX_BUFFER_HPP
#define RANDAR_RENDER_VERTEX_BUFFER_HPP

#include <randar/Render/GlBuffer.hpp>
#include <randar/Render/Vertex.hpp>

namespace randar
{
    /**
     * A high-level "buffer" of vertices composed of multiple OpenGL buffers.
     */
    class VertexBuffer : virtual public GraphicsContextResource
    {
    protected:
        FloatArrayBuffer positionBuffer;
        FloatArrayBuffer colorBuffer;

    public:
        /**
         * Constructor.
         *
         * Immediately initializes an empty vertex buffer on a context.
         */
        VertexBuffer(GraphicsContext& context);

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
        void initialize();

        /**
         * Uninitializes the vertex buffer from a context.
         *
         * Nothing happens if not initialized. Never throws an exception.
         */
        void uninitialize();

        /**
         * Whether this vertex buffer is initialized on a context.
         */
        bool isInitialized() const;

        /**
         * Syncs local data to the OpenGL buffers.
         */
        void sync();

        /**
         * Appends a new vertex.
         */
        void append(const Vertex& vertex);

        /**
         * Retrieves the vertex at the desired index.
         *
         * Throws an exception if the index exceeds the buffer size.
         */
        //Vertex get(uint32_t index) const;
    };
}

#endif
