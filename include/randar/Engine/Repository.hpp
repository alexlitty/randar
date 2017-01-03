#ifndef RANDAR_ENGINE_REPOSITORY_HPP
#define RANDAR_ENGINE_REPOSITORY_HPP

#include <randar/Engine/Gpu.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Utility/Map.hpp>

namespace randar
{
    /**
     * An organized collection of project resources.
     *
     * Repositories track resources and handle their creation, external
     * construction requirements (think OpenGL calls), importing from files
     * (think mesh files), exporting to proprietary formats, and complete
     * destruction and cleanup.
     *
     * Resources are externally identified by integers. When a resource is
     * required, always call the repository to retrieve the latest underlying
     * pointer; The "same" resource with the same ID may use a different
     * pointer over time. The ID, however, is guaranteed to be associated with
     * the desired resource, wherever it may be located and instanced as.
     */
    class Repository
    {
    public:
        Gpu& gpu;

        Repository(Gpu& initGpu = randar::getDefaultGpu());
        ~Repository();
    };

    /**
     * Default repository instance.
     *
     * Using this repository is all the engine should ever require, but you're
     * welcome to create further instances for whatever evil plan you have.
     */
    Repository& getDefaultRepository();
}

#endif
