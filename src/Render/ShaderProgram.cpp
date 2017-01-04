#include <randar/Render/ShaderProgram.hpp>
#include <randar/Engine/Gpu.hpp>

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

void randar::ShaderProgram::initialize(randar::Gpu& gpu)
{
    gpu.initialize(*this);
}

void randar::ShaderProgram::destroy(randar::Gpu& gpu)
{
    gpu.destroy(*this);
}
