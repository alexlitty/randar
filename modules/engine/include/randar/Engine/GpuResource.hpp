#ifndef RANDAR_ENGINE_GPU_RESOURCE_HPP
#define RANDAR_ENGINE_GPU_RESOURCE_HPP

#include <GL/glew.h>
#include <randar/Engine/Resource.hpp>

namespace randar
{
    class Gpu;

    /**
     * A resource that represents a potential GPU concept.
     *
     * GpuResources are not present on a GPU at all times. In fact, these
     * resources may not be associated with any GPU whatsoever.
     */
    class GpuResource : virtual public Resource
    {
    protected:
        /**
         * The Gpu that is responsible for this resource, if any.
         */
        Gpu *gpu;

        /**
         * GPU identifier for this resource.
         *
         * For most resources, glName is 0 when the resource is not initialized
         * on the GPU.
         */
        ::GLuint glName;

    public:
        /**
         * Constructors and destructor.
         */
        GpuResource(Gpu* initGpu = nullptr);
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
