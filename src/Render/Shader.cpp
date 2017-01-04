#include <randar/Render/Shader.hpp>
#include <randar/Engine/Gpu.hpp>

randar::Shader::Shader(const std::string& initName)
: randar::Resource(initName)
{

}

randar::Shader::Shader(
    ::GLenum initShaderType,
    const std::string& initCode,
    const std::string& initName
) :
  randar::Resource(initName),
  shaderType(initShaderType),
  code(initCode)
{

}

randar::Shader::Shader(const randar::Shader& other)
: randar::Resource(other.name),
  shaderType(other.shaderType),
  code(other.code)
{

}

void randar::Shader::initialize(randar::Gpu& gpu)
{
    gpu.initialize(*this);
    this->initialized = true;
}

void randar::Shader::destroy(randar::Gpu& gpu)
{
    gpu.destroy(*this);
    this->initialized = false;
}

randar::Shader& randar::Shader::operator =(const randar::Shader& other)
{
    this->initialized = false;
    this->setGlName(0);

    this->name = other.name;
    this->shaderType = other.shaderType;
    this->code = other.code;

    return *this;
}
