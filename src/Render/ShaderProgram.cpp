#include <randar/Render/ShaderProgram.hpp>

const randar::Resource::Type randar::ShaderProgram::type = randar::Resource::SHADER_PROGRAM;
randar::Resource::Type randar::ShaderProgram::getType() const
{
    return this->type;
}

randar::ShaderProgram::ShaderProgram(
    randar::Shader& initVertexShader,
    randar::Shader& initFragmentShader,
    const std::string& initName
) :
  randar::Resource(initName),
  vertexShader(initVertexShader),
  fragmentShader(initFragmentShader)
{

}
