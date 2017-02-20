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
        FrameRange(const Frame& frame);

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
         * Retrieves the number of frames in this range.
         */
        uint32_t count() const;

        /**
         * Checks whether a frame is contained by this range.
         */
        bool contains(const Frame& other);
    };
}

#endif
