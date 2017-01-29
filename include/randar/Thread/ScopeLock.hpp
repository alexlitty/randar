#ifndef RANDAR_THREAD_SCOPE_LOCK_HPP
#define RANDAR_THREAD_SCOPE_LOCK_HPP

#include <randar/Thread/Lock.hpp>

namespace randar
{
    /**
     * A lock that owns an object for the lock's lifetime.
     *
     * Immediately owns the object, and releases ownership upon
     * destruction.
     */
    class ScopeLock : public Lock
    {
    public:
        ScopeLock(Lockable& initObject);
    };
}

#endif
