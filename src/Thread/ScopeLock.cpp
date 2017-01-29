#include <randar/Thread/ScopeLock.hpp>

randar::ScopeLock::ScopeLock(randar::Lockable& initObject)
: randar::Lock(initObject)
{
    this->lock();
}
