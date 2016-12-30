#include <randar/Engine/Resource.hpp>

randar::Resource::~Resource()
{

}

bool randar::Resource::hasConsumers()
{
    return this->consumers != 0;
}

void randar::Resource::incrementConsumer()
{
    this->consumers++;
}

void randar::Resource::decrementConsumer()
{
    this->consumers--;
}
