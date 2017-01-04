#ifndef RANDAR_RENDER_SHADER_PROGRAM_HPP
#define RANDAR_RENDER_SHADER_PROGRAM_HPP

#include <randar/Render/Shader.hpp>

namespace randar
{
    struct ShaderProgram : virtual public GpuResource
    {
        Shader& vertexShader;
        Shader& fragmentShader;

        ShaderProgram(
            Shader& initVertexShader,
            Shader& initFragmentShader,
            const std::string& initName = "");

        virtual void initialize(Gpu& gpu) override;
        virtual void destroy(Gpu& gpu) override;
    };
}

#endif
