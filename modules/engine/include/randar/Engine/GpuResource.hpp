#ifndef RANDAR_ENGINE_GPU_RESOURCE_HPP
#define RANDAR_ENGINE_GPU_RESOURCE_HPP

#include <GL/glew.h>
#include <randar/Engine/Resource.hpp>

namespace randar
{
    class GpuResource : virtual public Resource
    {
    protected:
        ::GLuint glName;

    public:
        /**
         * Constructors and destructor.
         */
        GpuResource();
        GpuResource(const GpuResource& other);
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

        /**
         * Assignment operator.
         */
        GpuResource& operator =(const GpuResource& other);
    };
}

#endif
