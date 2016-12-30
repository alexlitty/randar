#ifndef RANDAR_ENGINE_RESOURCE_CONSUMER_HPP
#define RANDAR_ENGINE_RESOURCE_CONSUMER_HPP

#include <randar/Engine/Repository.hpp>

namespace randar
{
    class ResourceConsumer
    {
        Repository& repository;

        std::map<std::string, unsigned int> textures;
        std::map<std::string, unsigned int> shaders;
        std::map<std::string, unsigned int> shaderPrograms;

    public:
        ResourceConsumer(Repository& initRepository = randar::getDefaultRepository());
        virtual ~ResourceConsumer();

        /**
         * Textures.
         */
        Texture& getTexture(const std::string& name = "");
        Texture& requireTexture(
            unsigned int width,
            unsigned int height,
            const std::string& name = "");
        void disownTexture(const std::string& name);

        /**
         * Shaders.
         */
        Shader& getShader(const std::string& name = "");
        Shader& requireShader(
            const std::string& code,
            ::GLenum type,
            const std::string& name = "");
        void disownShader(const std::string& name);

        /**
         * Shader programs.
         */
        ShaderProgram& getShaderProgram(const std::string& name = "");
        ShaderProgram& requireShaderProgram(
            const Shader& vertexShader,
            const Shader& fragmentShader,
            const std::string& name = "");
        void disownShaderProgram(const std::string& name);
    };
}

#endif
