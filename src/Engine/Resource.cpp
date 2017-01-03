#include <randar/Engine/Resource.hpp>

randar::Resource::Resource(const std::string& initName)
: name(initName),
  initialized(false)
{
}

randar::Resource::~Resource()
{

}

randar::Resource::Type randar::Resource::getType() const
{
    return randar::Resource::INVALID;
}

bool randar::Resource::isAggregateResource() const
{
    return false;
}

bool randar::Resource::isGpuResource() const
{
    return false;
}
