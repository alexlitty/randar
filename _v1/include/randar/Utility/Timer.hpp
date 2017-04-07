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
        Timer();

        double getMilliseconds() const;
        double getMicroseconds() const;
        std::string get() const;
    };
}

#endif
