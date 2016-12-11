#ifndef RANDAR_RENDER_VERTICES_HPP
#define RANDAR_RENDER_VERTICES_HPP

#include <randar/render/RenderState.hpp>
#include <randar/render/Vertex.hpp>

namespace randar
{
    /**
     * A collection of vertices that can be sent to the GPU for drawing.
     */
    class Vertices
    {
        GLuint vertexArray;
        GLuint vertexBuffer;
        GLenum primitive;

        // @todo: Start relying on GPU-side vertices.
        std::vector<Vertex> vertices;

    public:

        Vertices(GLenum initPrimitive = GL_POINTS);
        Vertices(const Vertices& other);
        ~Vertices();

        /**
         * Sets how the vertices should be interpreted.
         */
        void setPrimitive(GLenum primitive);

        /**
         * Clears all vertices.
         */
        void clear();

        /**
         * Retrieves the number of vertices in this collection.
         */
        unsigned int getVertexCount() const;

        /**
         * Sends this buffer's data to the GPU.
         */
        void send();

        /**
         * Appends a new vertex to the buffer.
         */
        void append(Vertex& vertex);

        /**
         * Draws the vertices in this buffer.
         */
        void draw(RenderState& state) const;

        /**
         * Writeable access to individual vertices.
         */
        Vertex& operator[](unsigned int index);
    };
}

#endif
