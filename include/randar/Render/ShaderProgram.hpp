#ifndef RANDAR_RENDER_SHADER_PROGRAM_HPP
#define RANDAR_RENDER_SHADER_PROGRAM_HPP

#include <randar/Render/Shader.hpp>

namespace randar
{
    struct ShaderProgram : virtual public GpuResource
    {
        const static Resource::Type type;
        virtual Resource::Type getType() const override;

        Shader& vertexShader;
        Shader& fragmentShader;

        ShaderProgram(
            Shader& initVertexShader,
            Shader& initFragmentShader,
            const std::string& initName = "");

    };
}

#endif
