#include <randar/Render/Shader.hpp>
#include <randar/Engine/Gpu.hpp>

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

void randar::Shader::initialize(randar::Gpu& gpu)
{
    gpu.initialize(*this);
}

void randar::Shader::destroy(randar::Gpu& gpu)
{
    gpu.destroy(*this);
}
