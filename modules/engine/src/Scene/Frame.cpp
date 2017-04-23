#include <limits>
#include <stdexcept>
#include <randar/Scene/Frame.hpp>

// An easily-accessible instance of a final frame.
randar::Frame randar::Frame::Final(std::numeric_limits<uint32_t>::max());

// Constructor.
randar::Frame::Frame(uint32_t initId)
: id(initId)
{

}

// Checks whether this is the final frame.
bool randar::Frame::isFinal() const
{
    return *this == randar::Frame::Final;
}

// Retrieves the underlying frame ID.
uint32_t randar::Frame::get() const
{
    if (this->isFinal()) {
        throw std::runtime_error("Retrieving ID of final frame");
    }

    return this->id;
}

randar::Frame::operator uint32_t() const
{
    return this->get();
}

// Assignment operator.
randar::Frame& randar::Frame::operator =(uint32_t newId)
{
    this->id = newId;
    return *this;
}

// Comparison operators.
bool randar::Frame::operator ==(const randar::Frame& other)
{
    return this->id == other.id;
}

bool randar::Frame::operator !=(const randar::Frame& other)
{
    return !(*this == other);
}

bool randar::Frame::operator >(const randar::Frame& other)
{
    return this->id > other.id;
}

bool randar::Frame::operator >=(const randar::Frame& other)
{
    return this->id >= other.id;
}

bool randar::Frame::operator <(const randar::Frame& other)
{
    return this->id < other.id;
}

bool randar::Frame::operator <=(const randar::Frame& other)
{
    return this->id <= other.id;
}
