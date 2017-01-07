#include <randar/Render/ShaderProgram.hpp>
#include <randar/Engine/Gpu.hpp>

randar::ShaderProgram::ShaderProgram(const std::string& initName)
: randar::Resource(initName)
{

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

void randar::ShaderProgram::initialize()
{
    this->gpu.initialize(*this);
    this->initialized = true;
}

void randar::ShaderProgram::destroy()
{
    this->gpu.destroy(*this);
    this->initialized = false;
}
