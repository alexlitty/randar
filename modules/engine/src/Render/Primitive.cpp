#include <stdexcept>
#include <randar/Render/Primitive.hpp>

// Converts a Randar primitive to an OpenGL primitive.
GLenum randar::openglPrimitive(randar::Primitive primitive)
{
    switch (primitive) {
        case randar::Primitive::Point:
            return GL_POINTS;

        case randar::Primitive::Triangle:
            return GL_TRIANGLES;

        default:
            throw std::runtime_error("Invalid rendering primitive");
    }
}
