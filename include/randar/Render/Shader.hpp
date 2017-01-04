#ifndef RANDAR_RENDER_SHADER_HPP
#define RANDAR_RENDER_SHADER_HPP

#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct Shader : virtual public GpuResource
    {
        const GLenum shaderType;
        const std::string code;

        Shader(
            ::GLenum initShaderType,
            const std::string& initCode,
            const std::string& initName = ""
        );

        virtual void initialize(Gpu& gpu) override;
        virtual void destroy(Gpu& gpu) override;
    };
}

#endif
