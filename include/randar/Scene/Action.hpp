#ifndef RANDAR_SCENE_ACTION_HPP
#define RANDAR_SCENE_ACTION_HPP

#include <string>
#include <randar/Scene/FrameRange.hpp>
#include <randar/Utility/Json.hpp>

namespace randar
{
    struct Action
    {
        std::string type;
        FrameRange frames;

        /**
         * Constructor.
         */
        Action(
            const std::string& initType,
            const FrameRange& initFrames);

        /**
         * Destructor.
         */
        virtual ~Action();

        /**
         * Applies a single frame of this action to the scene.
         */
        virtual void apply() = 0;

        /**
         * Returns a representation of this action as JSON.
         */
        virtual Json toJson() const = 0;
    };
}

#endif
