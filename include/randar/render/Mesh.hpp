#ifndef RANDAR_RENDER_MESH_HPP
#define RANDAR_RENDER_MESH_HPP

#include <randar/render/Vertices.hpp>

namespace randar
{
    class Mesh : virtual public Drawable
    {
        GLuint indexBuffer;
        std::vector<unsigned int> indices;

    public:
        Vertices vertices;

        Mesh();
        Mesh(const Mesh& other);
        ~Mesh();

        void appendVertex(const Vector& position, const Color& color = Color(1.0f, 1.0f, 1.0f));
        void appendVertex(const Vertex& vertex);
        void appendFace(unsigned int a, unsigned int b, unsigned int c);

        void bind() const;
        void send() const;

        void draw() const;
    };
}

#endif
