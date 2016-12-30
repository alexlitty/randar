#ifndef RANDAR_RENDER_SHADER_HPP
#define RANDAR_RENDER_SHADER_HPP

#include <string>
#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct Shader : virtual public GpuResource
    {
        const GLenum type;
        const std::string code;

        Shader(
            ::GLuint initGlName,
            ::GLenum initType,
            std::string initCode
        );
    };
}

#endif
