#include <randar/Render/Uniform.hpp>

// Default constructor.
randar::Uniform::Uniform()
: name("nonexistent"),
  location(-1)
{

}

// Constructor.
randar::Uniform::Uniform(const std::string& initName, ::GLint initLocation)
: name(initName),
  location(initLocation)
{

}

// Copy constructor.
randar::Uniform::Uniform(const Uniform& other)
: name(other.name),
  location(other.location)
{

}

// Move constructor.
randar::Uniform::Uniform(const Uniform&& other)
: name(std::move(other.name)),
  location(std::move(other.location))
{

}

// Gets the name of this uniform.
const std::string& randar::Uniform::getName() const
{
    return this->name;
}

// Gets the location of this uniform on the program.
::GLint randar::Uniform::getLocation() const
{
    return this->location;
}

// Assignment operator.
randar::Uniform& randar::Uniform::operator =(const randar::Uniform& other)
{
    this->name = other.name;
    this->location = other.location;
    return *this;
}
