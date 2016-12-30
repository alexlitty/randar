#include <iostream>
#include <randar/Engine/Repository.hpp>

randar::Repository::Repository(randar::Gpu& initGpu)
: gpu(initGpu)
{

}

randar::Repository::~Repository()
{
    if (this->textures.size() > 0
     || this->shaders.size() > 0
     || this->shaderPrograms.size() > 0) {
        std::cout << "Memory leak: Repository destructing with objects existing!" << std::endl;
    }
}

// Default repository instance.
randar::Repository& randar::getDefaultRepository()
{
    static Repository defaultRepository;
    return defaultRepository;
}
