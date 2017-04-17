#include <randar/Engine/Resource.hpp>
#include <randar/Engine/Gpu.hpp>

randar::Resource::Resource(const std::string& initName)
: name(initName)
{

}

randar::Resource::~Resource()
{

}

// Converts this resource to a JSON representation.
Json randar::Resource::toJson() const
{
    throw std::runtime_error("No serialization defined for resource");
}
