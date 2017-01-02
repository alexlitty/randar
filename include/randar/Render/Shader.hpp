#ifndef RANDAR_RENDER_SHADER_HPP
#define RANDAR_RENDER_SHADER_HPP

#include <string>
#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct Shader : virtual public GpuResource
    {
        const static Resource::Type type;
        virtual Resource::Type getType() const override;

        const GLenum shaderType;
        const std::string code;

        Shader(
            ::GLenum initShaderType,
            const std::string& initCode,
            const std::string& initName = ""
        );
    };
}

#endif
