#include <randar/Engine/Stringable.hpp>

// Implicitly converts this object to a string.
randar::Stringable::operator std::string() const
{
    return this->toString();
}

// Sends a stringable object to an output stream.
std::ostream& randar::operator <<(std::ostream &os, const randar::Stringable& object)
{
    return os << object.toString();
}
