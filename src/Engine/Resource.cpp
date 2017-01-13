#include <randar/Engine/Resource.hpp>
#include <randar/Engine/Gpu.hpp>

randar::Resource::Resource(const std::string& initName)
: gpu(randar::getDefaultGpu()),
  initialized(false),
  name(initName)
{

}

randar::Resource::~Resource()
{

}

// Whether this resource is initialized.
bool randar::Resource::isInitialized() const
{
    return this->initialized;
}

// Converts this resource to a JSON representation.
Json randar::Resource::toJson() const
{
    throw std::runtime_error("No serialization defined for resource");
}
