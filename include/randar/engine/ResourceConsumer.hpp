#ifndef RANDAR_ENGINE_RESOURCE_CONSUMER_HPP
#define RANDAR_ENGINE_RESOURCE_CONSUMER_HPP

#include <randar/engine/Repository.hpp>

namespace randar
{
    class ResourceConsumer
    {
        Repository& repository;

        std::map<std::string, unsigned int> shaders;
        std::map<std::string, unsigned int> shaderPrograms;

    public:
        ResourceConsumer(Repository& initRepository = randar::getDefaultRepository());
        virtual ~ResourceConsumer();

        /**
         * Shaders.
         */
        Shader& getShader(const std::string& name);
        Shader& requireShader(
            const std::string& name,
            const std::string& code,
            ::GLenum type);
        void disownShader(const std::string& name);

        /**
         * Shader programs.
         */
        ShaderProgram& getShaderProgram(const std::string& name);
        ShaderProgram& requireShaderProgram(
            const std::string& name,
            const Shader& vertexShader,
            const Shader& fragmentShader);
        void disownShaderProgram(const std::string& name);
    };
}

#endif
