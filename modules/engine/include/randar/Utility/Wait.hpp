#ifndef RANDAR_UTILITY_WAIT_HPP
#define RANDAR_UTILITY_WAIT_HPP

#include <cstdint>

namespace randar
{
    /**
     * Waits until a period of microseconds have passed.
     */
    void wait(uint32_t microseconds);
}

#endif
