#include <randar/Engine/ResourceConsumer.hpp>

randar::ResourceConsumer::ResourceConsumer(randar::Repository& initRepository)
: repository(initRepository)
{

}

randar::ResourceConsumer::~ResourceConsumer()
{
    while (this->textures.begin() != this->textures.end()) {
        this->disownTexture(**this->textures.begin());
    }

    while (this->shaders.begin() != this->shaders.end()) {
        this->disownShader(**this->shaders.begin());
    }

    while (this->shaderPrograms.begin() != this->shaderPrograms.end()) {
        this->disownShaderProgram(**this->shaderPrograms.begin());
    }
}

// Textures.
randar::Texture& randar::ResourceConsumer::requireTexture(
    unsigned int width,
    unsigned int height)
{
    Texture *texture = this->repository.gpu.createTexture(width, height);
    this->textures.insert(texture);
    return *texture;
}

void randar::ResourceConsumer::disownTexture(randar::Texture& texture)
{
    this->textures.erase(&texture);
    delete &texture;
}

// Shaders.
randar::Shader& randar::ResourceConsumer::requireShader(
    const std::string& code,
    ::GLenum type)
{
    Shader *shader = this->repository.gpu.createShader(code, type);
    this->shaders.insert(shader);
    return *shader;
}

void randar::ResourceConsumer::disownShader(randar::Shader& shader)
{
    this->shaders.erase(&shader);
    delete &shader;
}

// Shader programs.
randar::ShaderProgram& randar::ResourceConsumer::requireShaderProgram(
    const Shader& vertexShader,
    const Shader& fragmentShader)
{
    ShaderProgram *shaderProgram = this->repository.gpu.createShaderProgram(
        vertexShader,
        fragmentShader
    );
    this->shaderPrograms.insert(shaderProgram);
    return *shaderProgram;
}

void randar::ResourceConsumer::disownShaderProgram(ShaderProgram& shaderProgram)
{
    this->shaderPrograms.erase(&shaderProgram);
    delete &shaderProgram;
}
