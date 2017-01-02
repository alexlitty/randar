#include <randar/Render/Shader.hpp>

const randar::Resource::Type randar::Shader::type = randar::Resource::SHADER;
randar::Resource::Type randar::Shader::getType() const
{
    return this->type;
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
