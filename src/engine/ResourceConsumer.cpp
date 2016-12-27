#include <randar/engine/ResourceConsumer.hpp>

randar::ResourceConsumer::ResourceConsumer(randar::Repository& initRepository)
: repository(initRepository)
{

}

randar::ResourceConsumer::~ResourceConsumer()
{
    for (auto item : this->shaders) {
        this->repository.disownShader(item.second);
    }

    for (auto item : this->shaderPrograms) {
        this->repository.disownShaderProgram(item.second);
    }
}

// Shaders.
randar::Shader& randar::ResourceConsumer::getShader(const std::string& name)
{
    randar::assertKey(this->shaders, name);
    return this->repository.getShader(this->shaders[name]);
}

randar::Shader& randar::ResourceConsumer::requireShader(
    const std::string& name,
    const std::string& code,
    ::GLenum type)
{
    randar::assertNoKey(this->shaders, name);
    this->shaders[name] = this->repository.requireShader(code, type);
    return this->getShader(name);
}

void randar::ResourceConsumer::disownShader(const std::string& name)
{
    randar::assertKey(this->shaders, name);
    this->repository.disownShader(this->shaders[name]);
}

// Shader programs.
randar::ShaderProgram& randar::ResourceConsumer::getShaderProgram(const std::string& name)
{
    randar::assertKey(this->shaderPrograms, name);
    return this->repository.getShaderProgram(this->shaderPrograms[name]);
}

randar::ShaderProgram& randar::ResourceConsumer::requireShaderProgram(
    const std::string& name,
    const Shader& vertexShader,
    const Shader& fragmentShader)
{
    randar::assertNoKey(this->shaderPrograms, name);
    this->shaderPrograms[name] = this->repository.requireShaderProgram(
        vertexShader,
        fragmentShader
    );
    return this->getShaderProgram(name);
}

void randar::ResourceConsumer::disownShaderProgram(const std::string& name)
{
    randar::assertKey(this->shaderPrograms, name);
    this->repository.disownShaderProgram(this->shaderPrograms[name]);
}
