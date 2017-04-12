#ifndef RANDAR_ENGINE_GPU_RESOURCE_HPP
#define RANDAR_ENGINE_GPU_RESOURCE_HPP

#include <randar/Engine/Resource.hpp>
#include <randar/Engine/Glfw.hpp>

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
         * Whether this resource is initialized on the GPU.
         */
        virtual bool isInitialized() const;

        /**
         * OpenGL name assignment and retrieval.
         */
        void setGlName(::GLuint newGlName);
        GLuint getGlName() const;
        operator GLuint() const;
        operator GLuint*();
        operator GLuint&();
    };
}

#endif
