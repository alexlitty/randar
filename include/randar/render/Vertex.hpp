#ifndef RANDAR_RENDER_VERTEX_HPP
#define RANDAR_RENDER_VERTEX_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <randar/math/Vector.hpp>
#include <randar/render/Color.hpp>
#include <randar/render/VertexAttribute.hpp>

namespace randar
{
    struct Vertex
    {
        static std::vector<VertexAttribute> attributes;
        static unsigned int stride;
        static unsigned int size;

        Vector position;
        Color color;

        Vertex();
        Vertex(Vector initPosition, Color initColor);

        void appendTo(GLfloat* array) const;
    };
}

#endif
