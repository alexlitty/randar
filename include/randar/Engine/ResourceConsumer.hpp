#ifndef RANDAR_ENGINE_RESOURCE_CONSUMER_HPP
#define RANDAR_ENGINE_RESOURCE_CONSUMER_HPP

#include <randar/Engine/Repository.hpp>
#include <randar/Utility/Map.hpp>

namespace randar
{
    class ResourceConsumer
    {
        Repository& repository;
        std::map<Resource::Type, std::map<std::string, Resource*>> resources;

    public:
        /**
         * Constructor.
         */
        ResourceConsumer(Repository& initRepository = randar::getDefaultRepository())
        : repository(initRepository)
        {

        }

        /**
         * Destructor.
         */
        ~ResourceConsumer()
        {
            for (auto tResources : this->resources) {
                while (!tResources.second.empty()) {
                    this->detach((*tResources.second.begin()).second);
                }
            }
        }

        /**
         * Retrieves a resource associated with this object.
         */
        template <typename T>
        T& get(const std::string& name = "")
        {
            std::map<std::string, Resource*>& tResources = this->resources[T::type];
            if (!randar::hasKey(tResources, name)) {
                throw std::runtime_error("Retrieving resource that does not exist");
            }
            return *dynamic_cast<T*>(tResources[name]);
        }

        template <typename T>
        const T& get(const std::string& name = "") const
        {
            const std::map<std::string, Resource*>& tResources = this->resources.at(T::type);
            if (!randar::hasKey(tResources, name)) {
                throw std::runtime_error("Retrieving resources that does not exist");
            }
            return *dynamic_cast<T*>(tResources.at(name));
        }

        /**
         * Associates a resource with this object.
         *
         * If the resource is not initialized yet, it is initialized here.
         *
         * In the future, this may check for existing resources that are just
         * duplicates of the requested resource, and attach any existing
         * resource instead.
         */
        void attach(Resource* resource)
        {
            // Ensure resource name is unique.
            std::map<std::string, Resource*>& tResources = this->resources[resource->getType()];
            if (randar::hasKey(tResources, resource->name)) {
                throw std::runtime_error("Attaching resource to consumer, but resource already exists");
            }

            // Initialize.
            if (!resource->initialized) {

                // Simple GPU resource.
                if (resource->isGpuResource()) {
                    this->repository.gpu.initialize(
                        dynamic_cast<GpuResource*>(resource)
                    );
                }

                // More than a simple GPU resource.
                else {
                    if (resource->getType() == Resource::MESH) {
                        Mesh *mesh = dynamic_cast<Mesh*>(resource);
                        this->repository.gpu.initialize(mesh->vertexBuffer);
                        this->repository.gpu.initialize(mesh->indexBuffer);
                    }
                }

            }

            // Associate resource.
            tResources[resource->name] = resource;
        }

        /**
         * Breaks all association with a resource and this object.
         *
         * Also destroys the resource if no other objects are associated.
         */
        void detach(Resource* resource)
        {
            this->detach(
                resource->getType(),
                resource->name
            );
        }

        void detach(Resource::Type type, const std::string& name)
        {
            // Ensure resource is associated.
            std::map<std::string, Resource*>& tResources = this->resources[type];
            if (!randar::hasKey(tResources, name)) {
                throw std::runtime_error("Detaching resource from consumer, but resource is not associated");
            }

            // Destroy.
            Resource* resource = tResources[name];
            if (resource->isGpuResource()) {
                this->repository.gpu.destroy(
                    dynamic_cast<GpuResource*>(resource)
                );
            }

            else {
                if (resource->getType() == Resource::MESH) {
                    Mesh *mesh = dynamic_cast<Mesh*>(resource);
                    this->repository.gpu.destroy(&mesh->vertexBuffer);
                    this->repository.gpu.destroy(&mesh->vertexBuffer);
                }
            }

            // Detach.
            tResources.erase(name);
        }
    };
}

#endif
