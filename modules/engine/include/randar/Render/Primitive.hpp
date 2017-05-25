#ifndef RANDAR_RENDER_PRIMITIVE_HPP
#define RANDAR_RENDER_PRIMITIVE_HPP

#include <randar/Utility/Gl.hpp>

namespace randar
{
    /**
     * Rendering primitives which describe modes of vertex interpretation.
     */
    enum class Primitive
    {
        Point,
        Triangle
    };

    /**
     * Converts a Randar primitive to an OpenGL primitive.
     */
    GLenum openglPrimitive(Primitive primitive);
}

#endif
