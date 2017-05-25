#ifndef RANDAR_UTILITY_TIMER_HPP
#define RANDAR_UTILITY_TIMER_HPP

#include <chrono>
#include <string>

namespace randar
{
    class Timer
    {
        std::chrono::high_resolution_clock::time_point start;

    public:
        /**
         * Constructor.
         *
         * Starts the timer immediately, setting the start time to the current
         * time.
         */
        Timer();

        /**
         * Resets the timer.
         *
         * Sets the start time to the current time.
         */
        void reset();

        /**
         * Returns the elapsed time.
         */
        double microseconds() const;
        double milliseconds() const;
        double seconds() const;

        /**
         * Waits until a period of microseconds have elapsed.
         */
        void wait(uint32_t microseconds) const;

        /**
         * Generates a human-friendly representation of elapsed time.
         */
        std::string toString() const;
    };
}

#endif
