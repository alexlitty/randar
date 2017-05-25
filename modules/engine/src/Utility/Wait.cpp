#include <unistd.h>
#include <randar/Utility/Wait.hpp>

// Waits until a period of microseconds have passed.
void randar::wait(uint32_t microseconds)
{
    ::usleep(microseconds);
}
