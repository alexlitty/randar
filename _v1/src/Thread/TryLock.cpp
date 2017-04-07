#include <randar/Thread/TryLock.hpp>

randar::TryLock::TryLock(randar::Lockable& initObject)
: randar::Lock(initObject)
{
    this->tryLock();
}
