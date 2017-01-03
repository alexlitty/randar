#ifndef RANDAR_SHAPE_SHAPE_HPP
#define RANDAR_SHAPE_SHAPE_HPP

#include <vector>
#include <randar/Render/Vertex.hpp>

namespace randar
{
    /**
     * Representation of a shape.
     */
    struct Shape
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
    };
}

#endif
