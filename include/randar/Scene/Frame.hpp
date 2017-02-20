#ifndef RANDAR_SCENE_FRAME_HPP
#define RANDAR_SCENE_FRAME_HPP

#include <cstdint>

namespace randar
{
    /**
     * Identifier for a particular scene frame.
     */
    class Frame
    {
        /**
         * Internal identifier for the frame.
         *
         * If set to the maximum value, it represents the final scene frame.
         */
        uint32_t id;

    public:
        /**
         * An easily-accessible instance of a final frame.
         */
        static Frame Final;

        /**
         * Constructor.
         */
        Frame(uint32_t initId);

        /**
         * Checks whether this is the final frame.
         */
        bool isFinal() const;

        /**
         * Retrieves the underlying frame ID.
         */
        uint32_t get() const;
        operator uint32_t() const;

        /**
         * Assignment operator.
         */
        Frame& operator =(uint32_t newId);

        /**
         * Comparison operators.
         */
        bool operator ==(const Frame& other);
        bool operator !=(const Frame& other);
    };
}

#endif
