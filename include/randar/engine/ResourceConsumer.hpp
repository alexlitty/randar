#ifndef RANDAR_ENGINE_RESOURCE_CONSUMER_HPP
#define RANDAR_ENGINE_RESOURCE_CONSUMER_HPP

#include <map>
#include <string>
#include <randar/engine/Repository.hpp>

namespace randar
{
    class ResourceConsumer
    {
        Repository& repository;
        std::map<std::string, unsigned int> textureIds;

    public:
        ResourceConsumer(Repository& initRepository = randar::primaryRepository);
    };
}

#endif
