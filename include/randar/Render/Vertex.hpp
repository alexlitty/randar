#ifndef RANDAR_RENDER_VERTEX_HPP
#define RANDAR_RENDER_VERTEX_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <randar/Math/Vector.hpp>
#include <randar/Render/Color.hpp>
#include <randar/Render/VertexAttribute.hpp>

namespace randar
{
    struct TextureCoordinate
    {
        float u;
        float v;
    };

    struct Vertex
    {
        Vector position;
        Color color;
        unsigned char boneIndex[4];
        unsigned char boneWeight[4];
        TextureCoordinate textureCoordinate;

        Vertex();
        Vertex(Vector initPosition, Color initColor);

        void appendTo(GLfloat* array) const;
    };
}

#endif
