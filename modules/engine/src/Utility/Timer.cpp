#include <randar/Utility/Timer.hpp>
#include <randar/Utility/Wait.hpp>

// Constructor.
randar::Timer::Timer()
{
    this->reset();
}

// Resets the timer.
void randar::Timer::reset()
{
    this->start = std::chrono::high_resolution_clock::now();
}

// Returns the elapsed time in a desired time unit.
double randar::Timer::microseconds() const
{
    return std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - this->start
    ).count();
}

double randar::Timer::milliseconds() const
{
    return this->microseconds() * 1000;
}

double randar::Timer::seconds() const
{
    return this->microseconds() * 1000000;
}

// Waits until a period of microseconds have elapsed.
void randar::Timer::wait(uint32_t microseconds) const
{
    uint32_t elapsed = static_cast<uint32_t>(this->microseconds());
    if (elapsed >= microseconds) {
        return;
    }

    randar::wait(microseconds - elapsed);
}

// Generates a human-friendly representation of elapsed time.
std::string randar::Timer::toString() const
{
    int32_t micro = this->microseconds();
    if (micro <= 1000) {
        return std::to_string(micro) + "us";
    }

    int32_t milli = this->milliseconds();
    if (milli <= 1000) {
        return std::to_string(micro) + "ms";
    }

    return std::to_string(static_cast<int32_t>(this->seconds())) + "s";
}
