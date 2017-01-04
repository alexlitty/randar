#ifndef RANDAR_RENDER_SHADER_HPP
#define RANDAR_RENDER_SHADER_HPP

#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct Shader : virtual public GpuResource
    {
        GLenum shaderType;
        std::string code;

        Shader(const std::string& initName = "");
        Shader(
            ::GLenum initShaderType,
            const std::string& initCode,
            const std::string& initName = ""
        );
        Shader(const Shader& other);

        virtual void initialize(Gpu& gpu) override;
        virtual void destroy(Gpu& gpu) override;

        Shader& operator =(const Shader& other);
    };
}

#endif
