#ifndef RANDAR_SHAPE_PLANE_HPP
#define RANDAR_SHAPE_PLANE_HPP

#include <randar/render/Mesh.hpp>

namespace randar
{
    class Plane : public Mesh
    {
    public:
        Plane(const Vector& min, const Vector& max);
    };
}

#endif
