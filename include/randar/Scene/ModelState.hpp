#ifndef RANDAR_SCENE_MODEL_STATE_HPP
#define RANDAR_SCENE_MODEL_STATE_HPP

#include <randar/Render/Model.hpp>
#include <randar/Scene/TransformState.hpp>

namespace randar
{
    struct ModelState : public TransformState
    {
        /**
         * Sets this state using an existing model.
         */
        void set(const Model& other);

        /**
         * Applies this state to a model.
         */
        void apply(Model& other);
    };
}

#endif
