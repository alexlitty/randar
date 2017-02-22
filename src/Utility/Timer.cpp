#include <randar/Utility/Timer.hpp>

randar::Timer::Timer()
{
    this->start = std::chrono::high_resolution_clock::now();
}

double randar::Timer::getMilliseconds() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - this->start
    ).count();
}

double randar::Timer::getMicroseconds() const
{
    return std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - this->start
    ).count();
}

std::string randar::Timer::get() const
{
    int32_t micro = this->getMicroseconds();
    if (micro <= 1000) {
        return std::to_string(micro) + "us";
    }

    return std::to_string((int32_t)this->getMilliseconds()) + "ms";
}
