#ifndef RANDAR_ENGINE_RESOURCE_HPP
#define RANDAR_ENGINE_RESOURCE_HPP

#include <randar/Utility/Json.hpp>

namespace randar
{
    /**
     * Resolve circular dependencies with the GPU.
     */
    class Gpu;

    /**
     * A resource, which may or may not be fully loaded into memory.
     *
     * Resource objects begin as a self-description. They can initialized into
     * memory and freed as necessary, as many times as needed, using this same
     * object.
     */
    class Resource
    {
    protected:
        Gpu& gpu;
        bool initialized;

    public:
        /**
         * A user-defined name for this resource.
         */
        std::string name;

        /**
         * Constructor.
         */
        Resource(const std::string& initName = "");

        /**
         * Destructor.
         */
        virtual ~Resource();

        /**
         * Initialize this resource and bring it into memory.
         */
        virtual void initialize() = 0;

        /**
         * Whether this resource is initialized.
         */
        bool isInitialized() const;

        /**
         * Destroys this resource and frees it from memory.
         */
        virtual void destroy() = 0;

        /**
         * Converts this resource to a JSON representation.
         */
        virtual Json toJson() const;
    };
}

#endif
