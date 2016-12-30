#ifndef RANDAR_ENGINE_RESOURCE_HPP
#define RANDAR_ENGINE_RESOURCE_HPP

namespace randar
{
    class Resource
    {
        unsigned int consumers = 0;

    public:
        virtual ~Resource();
        bool hasConsumers();
        void incrementConsumer();
        void decrementConsumer();
    };
}

#endif
