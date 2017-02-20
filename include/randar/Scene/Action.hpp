#ifndef RANDAR_SCENE_ACTION_HPP
#define RANDAR_SCENE_ACTION_HPP

#include <cstdint>
#include <string>
#include <randar/Scene/FrameRange.hpp>

namespace randar
{
    struct Action
    {
        const std::string type;
        FrameRange frames;

        /**
         * Constructor.
         */
        Action(
            const std::string& initType,
            const FrameRange& initFrames);

        /**
         * Applies this action to the scene.
         */
        virtual void apply(uint32_t frames = 1) = 0;
    };
}

#endif
