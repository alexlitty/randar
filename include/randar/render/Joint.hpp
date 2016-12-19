#ifndef RANDAR_RENDER_JOINT_HPP
#define RANDAR_RENDER_JOINT_HPP

#include <randar/render/JointPose.hpp>

namespace randar
{
    struct Joint : virtual public JointPose
    {
        std::string name;

        Joint *parent = nullptr;
        JointPose basePose;

        glm::mat4 getPoseMatrix() const;
    };
}

#endif
