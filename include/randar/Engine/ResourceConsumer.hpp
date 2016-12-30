#ifndef RANDAR_ENGINE_RESOURCE_CONSUMER_HPP
#define RANDAR_ENGINE_RESOURCE_CONSUMER_HPP

#include <randar/Engine/Repository.hpp>
#include <randar/Utility/Vector.hpp>

namespace randar
{
    class ResourceConsumer
    {
        Repository& repository;

        RepositoryResource<Texture> textures;
        RepositoryResource<Shader> shaders;
        RepositoryResource<ShaderProgram> shaderPrograms;

    public:
        ResourceConsumer(Repository& initRepository = randar::getDefaultRepository());
        virtual ~ResourceConsumer();

        /**
         * Textures.
         */
        Texture& requireTexture(unsigned int width, unsigned int height);
        void disownTexture(Texture& texture);

        /**
         * Shaders.
         */
        Shader& requireShader(const std::string& code, ::GLenum type);
        void disownShader(Shader& shader);

        /**
         * Shader programs.
         */
        ShaderProgram& requireShaderProgram(
            const Shader& vertexShader,
            const Shader& fragmentShader);
        void disownShaderProgram(ShaderProgram& shader);
    };
}

#endif
