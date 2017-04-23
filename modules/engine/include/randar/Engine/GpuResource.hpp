#ifndef RANDAR_ENGINE_GPU_RESOURCE_HPP
#define RANDAR_ENGINE_GPU_RESOURCE_HPP

#include <GL/glew.h>
#include <randar/Engine/Resource.hpp>
#include <randar/System/GraphicsContext.hpp>
#include <randar/Utility/Unassignable.hpp>

namespace randar
{
    class Gpu;

    /**
     * A resource that represents a potential GPU concept.
     *
     * GpuResources are not present on a GPU at all times. In fact, these
     * resources may not be associated with any GPU whatsoever.
     */
    class GpuResource : virtual public Resource, public Unassignable
    {
    protected:
        /**
         * The Gpu that is responsible for this resource, if any.
         *
         * @deprecated
         */
        Gpu *gpu;

        /**
         * Graphics context that is responsible for this resource.
         */
        GraphicsContext *ctx;

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
        GpuResource(GraphicsContext& initCtx);
        GpuResource(Gpu* initGpu = nullptr);
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
