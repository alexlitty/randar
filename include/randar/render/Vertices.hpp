#ifndef RANDAR_RENDER_VERTICES_HPP
#define RANDAR_RENDER_VERTICES_HPP

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
        std::vector<float> attributeOffsets;
        GLenum primitive;

        // @todo: Start relying on GPU-side vertices.
        std::vector<Vertex> vertices;

    public:

        Vertices(GLenum initPrimitive = GL_POINTS);
        ~Vertices();

        /**
         * Sets how the vertices should be interpreted.
         */
        void setPrimitive(GLenum primitive);

        /**
         * Sends this buffer's data to the GPU.
         */
        void send();

        /**
         * Appends a new vertex to the buffer.
         */
        void append(Vertex &vertex);

        /**
         * Draws the vertices in this buffer.
         */
        void draw() const;

        /**
         * Writeable access to individual vertices.
         */
        Vertex& operator[](unsigned int index);
    };
}

#endif
