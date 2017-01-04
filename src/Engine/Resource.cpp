#include <randar/Engine/Resource.hpp>

randar::Resource::Resource(const std::string& initName)
: name(initName),
  initialized(false)
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
