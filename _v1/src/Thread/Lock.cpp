#include <randar/Thread/Lock.hpp>

// Constructor.
randar::Lock::Lock(randar::Lockable& initObject)
: object(initObject),
  rawLock(initObject, std::defer_lock)
{

}

// Destructor.
randar::Lock::~Lock()
{
    this->unlock();
}

// Locks the object.
void randar::Lock::lock()
{
    this->rawLock.lock();
}

// Attempts to lock the object.
bool randar::Lock::tryLock()
{
    return this->rawLock.try_lock();
}

// Alias for tryLock.
bool randar::Lock::try_lock()
{
    return this->tryLock();
}

// Unlocks the object.
void randar::Lock::unlock()
{
    if (this->rawLock) {
        this->rawLock.unlock();
    }
}

// Checks if the lock is the owner of the object.
bool randar::Lock::isOwner() const
{
    return static_cast<bool>(this->rawLock);
}

randar::Lock::operator bool() const
{
    return this->isOwner();
}
