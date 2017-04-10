#include <randar/Thread/Lockable.hpp>

randar::Lockable::operator std::mutex&()
{
    return this->mutex;
}
