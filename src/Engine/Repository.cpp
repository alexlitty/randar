#include <iostream>
#include <randar/Engine/Repository.hpp>

randar::Repository::Repository(randar::Gpu& initGpu)
: gpu(initGpu)
{

}

randar::Repository::~Repository()
{
    if (this->shaders.size() > 0 || this->shaderPrograms.size() > 0) {
        std::cout << "Memory leak: Repository destructing with objects existing!" << std::endl;
    }
}

// Textures.
randar::Texture& randar::Repository::getTexture(unsigned int id)
{
    return *this->textures[id];
}

unsigned int randar::Repository::requireTexture(
    randar::Texture::Type type,
    unsigned int width,
    unsigned int height)
{
    return randar::insertAtAvailableKey(
        this->textures,
        this->gpu.createTexture(type, width, height)
    );
}

void randar::Repository::disownTexture(unsigned int id)
{
    randar::assertKey(this->textures, id);
    this->gpu.destroyTexture(this->textures[id]);
    this->textures.erase(id);
}

// Shaders.
randar::Shader& randar::Repository::getShader(unsigned int id)
{
    randar::assertKey(this->shaders, id);
    return *this->shaders[id];
}

unsigned int randar::Repository::requireShader(const std::string& code, ::GLenum type)
{
    return randar::insertAtAvailableKey(
        this->shaders,
        this->gpu.createShader(code, type)
    );
}

void randar::Repository::disownShader(unsigned int id)
{
    randar::assertKey(this->shaders, id);
    this->gpu.destroyShader(this->shaders[id]);
    this->shaders.erase(id);
}

// Shader programs.
randar::ShaderProgram& randar::Repository::getShaderProgram(unsigned int id)
{
    randar::assertKey(this->shaderPrograms, id);
    return *this->shaderPrograms[id];
}

unsigned int randar::Repository::requireShaderProgram(
    const Shader& vertexShader,
    const Shader& fragmentShader)
{
    return randar::insertAtAvailableKey(
        this->shaderPrograms,
        this->gpu.createShaderProgram(vertexShader, fragmentShader)
    );
}

void randar::Repository::disownShaderProgram(unsigned int id)
{
    randar::assertKey(this->shaderPrograms, id);
    this->gpu.destroyShaderProgram(this->shaderPrograms[id]);
    this->shaderPrograms.erase(id);
}

// Default repository instance.
randar::Repository& randar::getDefaultRepository()
{
    static Repository defaultRepository;
    return defaultRepository;
}
