#ifndef RANDAR_RENDER_JOINT_HPP
#define RANDAR_RENDER_JOINT_HPP

#include <randar/Math/Transform.hpp>

namespace randar
{
    /**
     * An isolated joint.
     *
     * Instantiations, parent connections, and matrix calculations are handled
     * by skeletons.
     */
    struct Joint : public Transform
    {

    };
}

#endif
