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

// Converts to a JavaScript value.
Awesomium::JSValue randar::Resource::toJs() const
{
    throw std::runtime_error("No conversion defined: Resource to JavaScript value");
}

// Converts to JSON.
std::string randar::Resource::toJson() const
{
    return randar::toJson(this->toJs());
}
