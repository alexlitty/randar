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
        ~Mesh();

        void bind() const;
        void send() const;

        void draw() const;
    };
}

#endif
