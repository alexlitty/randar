#ifndef RANDAR_THREAD_LOCKABLE_HPP
#define RANDAR_THREAD_LOCKABLE_HPP

#include <mutex>

namespace randar
{
    /**
     * Object that can be locked for multithreaded operations.
     */
    class Lockable
    {
        /**
         * The mutex used for locking.
         */
        std::mutex mutex;

    public:
        /**
         * Returns the underlying mutex.
         */
        operator std::mutex&();
    };
}

#endif
