#include <randar/Render/Shape.hpp>

randar::Geometry randar::sphere(float radius)
{
    Geometry shape;

    shape.append(Vertex(0, 0, 0));
    shape.append(Vertex(radius, 0, 0));
    shape.append(Vertex(radius, radius, 0));

    shape.append(Vertex(0, 0, 0));
    shape.append(Vertex(-radius, 0, 0));
    shape.append(Vertex(-radius, -radius, 0));

    return shape;
}
