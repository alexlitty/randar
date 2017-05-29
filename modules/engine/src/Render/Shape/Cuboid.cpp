#include <randar/Render/Shape.hpp>

randar::Geometry randar::cuboid(
    float width,
    float height,
    float depth,
    const randar::Palette& palette)
{
    randar::Geometry geo;
    Vertex vert;

    float rw = width / 2.0f;
    float rh = height / 2.0f;
    float rd = depth / 2.0f;

    // Front faces.
    vert.color = palette.color();
    vert.position.set(-rw, -rh, -rd);
    geo.append(vert);

    vert.position.set(rw, rh, -rd);
    geo.append(vert);

    vert.position.set(-rw, rh, -rd);
    geo.append(vert);

    vert.position.set(-rw, -rh, -rd);
    geo.append(vert);

    vert.position.set(rw, -rh, -rd);
    geo.append(vert);

    vert.position.set(rw, rh, -rd);
    geo.append(vert);

    // Back faces.
    return geo;
}
