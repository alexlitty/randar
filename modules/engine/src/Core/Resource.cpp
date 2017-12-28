#include <iostream>
#include <randar/Core/Resource.hpp>

randar::Resource::~Resource()
{

}

void randar::Resource::describe()
{
    std::cout << this->description() << std::endl;
}
