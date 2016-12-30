#ifndef RANDAR_RENDER_MESH_HPP
#define RANDAR_RENDER_MESH_HPP

#include <randar/render/Vertices.hpp>

namespace randar
{
    class Mesh
    {

    public:
        GLuint indexBuffer;
        std::vector<unsigned int> indices;
        Vertices vertices;

        Mesh();
        Mesh(const Mesh& other);
        ~Mesh();

        void appendVertex(const Vector& position, const Color& color = Color(1.0f, 1.0f, 1.0f));
        void appendVertex(const Vertex& vertex);
        void appendFace(unsigned int a, unsigned int b, unsigned int c);

        void bind() const;
        void send() const;
    };
}

#endif
