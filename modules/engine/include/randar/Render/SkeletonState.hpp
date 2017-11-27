#ifndef RANDAR_RENDER_SKELETON_STATE_HPP
#define RANDAR_RENDER_SKELETON_STATE_HPP

#include <unordered_map>
#include <randar/Render/Joint.hpp>

namespace randar
{
    /**
     * Collection of joint states for generic skeletons.
     *
     * If a joint on an applied skeleton does not exist in the state, it is
     * unmodified.
     */
    struct SkeletonState
    {
        std::unordered_map<std::string, Joint> joints;

        /**
         * Default constructor.
         */
        SkeletonState();

        /**
         * Whether a joint explicitly exists in the state.
         */
        bool has(const std::string& name);

        /**
         * Retrieves a joint in the state.
         *
         * If the joint does not exist yet, it is created then returned.
         */
        Joint& joint(const std::string& name);

        /**
         * Removes a joint from the state.
         *
         * If the joint does not exist, nothing happens.
         */
        void remove(const std::string& name);
    };
}

#endif
