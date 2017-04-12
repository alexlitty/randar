#ifndef RANDAR_PROJECT_RESOURCE_ID_HPP
#define RANDAR_PROJECT_RESOURCE_ID_HPP

#include <cstdint>

namespace randar
{
    class ResourceId
    {
        uint32_t *id;

    public:
        /**
         * Default constructor.
         *
         * Creates a null resource ID.
         */
        ResourceId();

        /**
         * Constructor.
         *
         * Creates a resource ID with the given integer.
         */
        ResourceId(uint32_t initid);

        /**
         * Copy constructor.
         */
        ResourceId(const ResourceId& other);

        /**
         * Move constructor.
         */
        ResourceId(ResourceId&& other);

        /**
         * Destructor.
         */
        ~ResourceId();

        /**
         * Sets the underlying ID.
         */
        void set(uint32_t newId);

        /**
         * Clears the underlying ID, making this a null resource ID.
         */
        void clear();

        /**
         * Checks whether this resource ID is null.
         */
        bool isNull() const;

        /**
         * Retrieves the underlying ID.
         *
         * Throws an error if this resource ID is null.
         */
        uint32_t get() const;
        operator uint32_t() const;

        /**
         * Assignment operator.
         */
        ResourceId& operator=(const ResourceId& other);
    };
}

#endif
