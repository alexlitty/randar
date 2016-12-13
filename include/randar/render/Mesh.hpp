#ifndef RANDAR_RENDER_MESH_HPP
#define RANDAR_RENDER_MESH_HPP

#include <randar/render/Vertices.hpp>

namespace randar
{
    class Mesh : virtual public Drawable
    {
        GLuint indexBuffer;

    public:
        Vertices vertices;

        Mesh();
        ~Mesh();

        void draw() const;
    };
}

#endif
