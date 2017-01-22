#include <randar/Engine/FileResource.hpp>

randar::FileResource::FileResource(const std::string& initFile)
: file(initFile)
{

}

void randar::FileResource::setFile(const std::string& newFile)
{
    this->file = newFile;
}

const std::string& randar::FileResource::getFile() const
{
    return this->file;
}
