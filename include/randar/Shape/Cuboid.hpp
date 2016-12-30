#ifndef RANDAR_SHAPE_CUBOID_HPP
#define RANDAR_SHAPE_CUBOID_HPP

#include <randar/Render/Mesh.hpp>

namespace randar
{
    class Cuboid : public Mesh
    {
    public:
        Cuboid(const Vector& min, const Vector& max);
    };
}

#endif
