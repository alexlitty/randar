#include <randar/Engine/Resource.hpp>

randar::Resource::Resource(const std::string& initName)
: initialized(false),
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
