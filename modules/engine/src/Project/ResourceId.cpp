#include <stdexcept>
#include <randar/Project/ResourceId.hpp>

// Default constructor.
randar::ResourceId::ResourceId()
: id(nullptr)
{

}

// Constructor.
randar::ResourceId::ResourceId(uint32_t initId)
: id(new uint32_t(initId))
{

}

// Copy constructor.
randar::ResourceId::ResourceId(const ResourceId& other)
: id(other.id == nullptr ? nullptr : new uint32_t(*other.id))
{

}

// Move constructor.
randar::ResourceId::ResourceId(ResourceId&& other)
: id(nullptr)
{
    std::swap(this->id, other.id);
}

// Destructor.
randar::ResourceId::~ResourceId()
{
    this->clear();
}

// Sets the ID.
void randar::ResourceId::set(uint32_t newId)
{
    this->clear();
    this->id = new uint32_t(newId);
}

// Clears the ID, making this a null resource ID.
void randar::ResourceId::clear()
{
    delete this->id;
    this->id = nullptr;
}

// Checks whether this resource ID is null.
bool randar::ResourceId::isNull() const
{
    return this->id == nullptr;
}

// Retrieves the underlying ID.
uint32_t randar::ResourceId::get() const
{
    if (this->isNull()) {
        throw std::logic_error("Cannot convert null resource ID to integer");
    }

    return *this->id;
}

randar::ResourceId::operator uint32_t() const
{
    return this->get();
}

// Assignment operator.
randar::ResourceId& randar::ResourceId::operator =(const randar::ResourceId& other)
{
    if (this->isNull()) {
        this->clear();
    } else {
        this->set(other.get());
    }

    return *this;
}
