#ifndef RANDAR_THREAD_TRY_LOCK_HPP
#define RANDAR_THREAD_TRY_LOCK_HPP

#include <randar/Thread/Lock.hpp>

namespace randar
{
    /**
     * A lock that attempts to own an object for the lock's lifetime.
     *
     * If the lock gained ownership, it is released upon destruction.
     */
    class TryLock : public Lock
    {
    public:
        TryLock(Lockable& initObject);
    };
}

#endif
