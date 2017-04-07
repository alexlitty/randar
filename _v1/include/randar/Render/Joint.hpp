#ifndef RANDAR_RENDER_JOINT_HPP
#define RANDAR_RENDER_JOINT_HPP

#include <randar/Render/JointPose.hpp>

namespace randar
{
    struct Joint : virtual public JointPose
    {
        /**
         * User-friendly name for this joint.
         */
        std::string name;

        /**
         * This joint's parent, in id and pointer forms.
         */
        int32_t parentId = -1;
        Joint *parent = nullptr;

        glm::mat4 getPoseMatrix() const;
    };
}

#endif
