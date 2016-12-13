#ifndef RANDAR_RENDER_JOINT_HPP
#define RANDAR_RENDER_JOINT_HPP

#include <randar/math/Transformable.hpp>

namespace randar
{
    struct Joint : virtual public Transformable
    {
        Joint *parent = nullptr;
    };
}

#endif
