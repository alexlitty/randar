#ifndef RANDAR_RESOURCE_DEFAULT_SHADER_PROGRAM_HPP
#define RANDAR_RESOURCE_DEFAULT_SHADER_PROGRAM_HPP

#include <randar/Render/ShaderProgram.hpp>

namespace randar
{
    extern Shader& getDefaultVertexShader();
    extern Shader& getDefaultFragmentShader();
    extern ShaderProgram& getDefaultShaderProgram();
}

#endif
