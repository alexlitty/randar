#include <iostream>
#include <randar/System/Resource.hpp>

randar::Resource::~Resource()
{

}

void randar::Resource::describe()
{
    std::cout << this->description() << std::endl;
}
