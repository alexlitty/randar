#ifndef RANDAR_ENGINE_GPU_RESOURCE_HPP
#define RANDAR_ENGINE_GPU_RESOURCE_HPP

#include <randar/Utility/OpenGL.hpp>

namespace randar
{
    struct GpuResource
    {
        const ::GLuint glName;

        GpuResource(::GLuint initGlName);
        virtual ~GpuResource();

        operator ::GLuint() const;
    };
}

#endif
