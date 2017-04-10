#ifndef RANDAR_SCENE_TRANSFORM_STATE_HPP
#define RANDAR_SCENE_TRANSFORM_STATE_HPP

#include <randar/Math/Transform.hpp>

namespace randar
{
    /**
     * A state of transformation.
     */
    struct TransformState
    {
        /**
         * The transform describing the state.
         */
        Transform transform;

        /**
         * Sets the transformation for this state.
         */
        void set(const Transform& other);

        /**
         * Applies this state to a transform.
         */
        void apply(Transform& other);
    };
}

#endif
