#include <randar/Render/Shader.hpp>

randar::Shader::Shader(
    ::GLuint initGlName,
    ::GLenum initType,
    std::string initCode
) :
  randar::GpuResource(initGlName),
  type(initType),
  code(initCode)
{

}
