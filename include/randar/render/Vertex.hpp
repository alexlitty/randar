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
        Vector position;
        Color color;
        unsigned char boneIndex[4];
        unsigned char boneWeight[4];

        Vertex();
        Vertex(Vector initPosition, Color initColor);

        void appendTo(GLfloat* array) const;
    };
}

#endif
