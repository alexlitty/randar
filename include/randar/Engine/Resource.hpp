#ifndef RANDAR_ENGINE_RESOURCE_HPP
#define RANDAR_ENGINE_RESOURCE_HPP

#include <string>

namespace randar
{
    struct Resource
    {
        enum Type
        {
            INVALID,

            // Aggregate resources.
            MESH,
            MODEL,

            // GPU resources.
            FRAMEBUFFER,
            INDEXBUFFER,
            RENDERBUFFER,
            SHADER,
            SHADER_PROGRAM,
            TEXTURE,
            VERTEXBUFFER
        };

        /**
         * A user-defined name for this resource.
         */
        std::string name;

        /**
         * Whether this resource is initialized.
         *
         * If uninitialized, this object is a "meta" reference to a resource
         * that simply isn't loaded yet. It represents a resource that *could*
         * exist.
         *
         * An initialized object could be uninitialized later.
         */
        bool initialized;

        /**
         * Constructor.
         */
        Resource(const std::string& initName = "");

        /**
         * Destructor.
         */
        virtual ~Resource();

        /**
         * Retrieves resource information.
         */
        virtual Resource::Type getType() const;
        virtual bool isAggregateResource() const;
        virtual bool isGpuResource() const;
    };
}

#endif
