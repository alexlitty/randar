#ifndef RANDAR_SCENE_FRAME_RANGE_HPP
#define RANDAR_SCENE_FRAME_RANGE_HPP

#include <randar/Scene/Frame.hpp>

namespace randar
{
    class FrameRange
    {
        Frame start;
        Frame end;

    public:
        /**
         * Constructor.
         */
        FrameRange(const Frame& initStart, const Frame& initEnd);

        /**
         * Validates this range.
         *
         * Throws an error upon failure.
         */
        void check() const;

        /**
         * Sets the range of frames.
         */
        void set(const Frame& newStart, const Frame& newEnd);
        void setStart(const Frame& newstart);
        void setEnd(const Frame& newEnd);

        /**
         * Checks whether a frame is contained by this range.
         */
        bool contains(const Frame& other);
    };
}

#endif
