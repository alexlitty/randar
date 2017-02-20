#ifndef RANDAR_SCENE_TRANSFORM_ACTION_HPP
#define RANDAR_SCENE_TRANSFORM_ACTION_HPP

#include <randar/Math/Transform.hpp>
#include <randar/Scene/Action.hpp>

namespace randar
{
    class TransformAction : virtual Action
    {
        /**
         * The target to receive the transformation.
         */
        Transform* target;

    public:
        /**
         * The transformation to apply to the target.
         */
        Transform transform;

        /**
         * Constructor.
         */
        TransformAction(
            const FrameRange& frames,
            Transform* initTarget);

        /**
         * Applies a single frame of this transformation to the target.
         */
        virtual void apply() override;
    };
}

#endif
