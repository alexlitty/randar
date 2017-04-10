#include <iostream>
#include <randar/Engine/Repository.hpp>

randar::Repository::Repository(randar::Gpu& initGpu)
: gpu(initGpu)
{

}

randar::Repository::~Repository()
{

}

// Default repository instance.
randar::Repository& randar::getDefaultRepository()
{
    static Repository defaultRepository;
    return defaultRepository;
}
