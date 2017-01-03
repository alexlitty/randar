#ifndef RANDAR_ENGINE_AGGREGATE_RESOURCE_HPP
#define RANDAR_ENGINE_AGGREGATE_RESOURCE_HPP

#include <randar/Engine/Gpu.hpp>
#include <randar/Engine/Resource.hpp>

namespace randar
{
    /**
     * A special kind of resource that is actually a collection of resources,
     * with some functionality that makes the resources useful together.
     */
    struct AggregateResource : virtual public Resource
    {
        virtual void initialize(Gpu& gpu) = 0;
        virtual void destroy(Gpu& gpu) = 0;
        
        /**
         * Retrieves resource information.
         */
        virtual bool isAggregateResource() const override;
    };
}

#endif
