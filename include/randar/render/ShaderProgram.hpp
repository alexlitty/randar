#ifndef RANDAR_RENDER_SHADER_PROGRAM_HPP
#define RANDAR_RENDER_SHADER_PROGRAM_HPP

#include <randar/render/Shader.hpp>

namespace randar
{
    class ShaderProgram
    {
        GLuint id;

    public:
        ShaderProgram(Shader &vertexShader, Shader &fragmentShader);
        ~ShaderProgram();
    };
}

#endif
