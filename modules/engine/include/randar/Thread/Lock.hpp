#ifndef RANDAR_THREAD_LOCK_HPP
#define RANDAR_THREAD_LOCK_HPP

#include <randar/Thread/Lockable.hpp>

namespace randar
{
    /**
     * A generic lock on a lockable object.
     *
     * May not be moved or copied.
     *
     * Does not immediately lock the object. If this lock owns the object upon
     * destruction, it is automatically unlocked.
     */
    class Lock
    {
        /**
         * Disable copy construction.
         */
        Lock(const Lock& other) = delete;
        Lock& operator =(const Lock& other) = delete;

    protected:
        Lockable& object;
        std::unique_lock<std::mutex> rawLock;

    public:
        /**
         * Constructor.
         *
         * Does not lock the object.
         */
        Lock(Lockable& initObject);

        /**
         * Destructor.
         *
         * Unlocks the object if this lock owns it.
         */
        ~Lock();

        /**
         * Locks the object.
         *
         * If the object is not immediately available for locking, this call
         * blocks until the object is available.
         */
        void lock();

        /**
         * Attempts to lock the object.
         */
        bool tryLock();

        /**
         * Alias for tryLock.
         *
         * Provided to make this class a C++ standard Lockable object.
         */
        bool try_lock();

        /**
         * Unlocks the object.
         *
         * Nothing happens if this lock does not own the object.
         */
        void unlock();

        /**
         * Checks if the lock is the owner of the object.
         */
        bool isOwner() const;
        operator bool() const;
    };
}

#endif
