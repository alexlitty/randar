#ifndef RANDAR_RENDER_SHADER_PROGRAM_HPP
#define RANDAR_RENDER_SHADER_PROGRAM_HPP

#include <randar/engine/GpuResource.hpp>

namespace randar
{
    struct ShaderProgram : virtual public GpuResource
    {
        ShaderProgram(::GLuint initGlName);
    };
}

#endif
