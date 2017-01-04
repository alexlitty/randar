#ifndef RANDAR_ENGINE_GPU_RESOURCE_HPP
#define RANDAR_ENGINE_GPU_RESOURCE_HPP

#include <randar/Engine/Resource.hpp>
#include <randar/Utility/OpenGL.hpp>

namespace randar
{
    class GpuResource : virtual public Resource
    {
    protected:
        ::GLuint glName;

    public:
        /**
         * Constructor and destructor.
         */
        GpuResource();
        ~GpuResource();

        /**
         * OpenGL name assignment and retrieval.
         */
        void setGlName(::GLuint newGlName);
        ::GLuint getGlName() const;
        operator ::GLuint() const;
        operator ::GLuint*();
        operator ::GLuint&();
    };
}

#endif
