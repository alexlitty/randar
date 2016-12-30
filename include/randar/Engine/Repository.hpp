#ifndef RANDAR_ENGINE_REPOSITORY_HPP
#define RANDAR_ENGINE_REPOSITORY_HPP

#include <set>
#include <randar/Engine/Gpu.hpp>
//#include <randar/Utility/Map.hpp>

namespace randar
{
    template <typename T>
    using RepositoryResource = std::set<T*>;

    /**
     * An organized repository of resources. Only responsible for storing
     * resources (or resource locations) -- not their creation, destruction,
     * or manipulation.
     *
     * Think of this like a cache of sorts, used by a resource consumer.
     */
    struct Repository
    {
        Gpu& gpu;

        RepositoryResource<Texture> textures;
        RepositoryResource<Shader> shaders;
        RepositoryResource<ShaderProgram> shaderPrograms;

        Repository(Gpu& initGpu = randar::getDefaultGpu());
        ~Repository();
    };

    /**
     * Default repository instance.
     *
     * Using this repository is all the suite should ever require, but you're
     * welcome to create further instances for whatever evil plan you have.
     */
    Repository& getDefaultRepository();
}

#endif
