#ifndef RANDAR_RENDER_RENDERBUFFER_HPP
#define RANDAR_RENDER_RENDERBUFFER_HPP

#include <randar/Engine/GpuResource.hpp>
#include <randar/System/GraphicsContext.hpp>

namespace randar
{
    class Renderbuffer : public GpuResource
    {
        /**
         * Type of renderbuffer.
         *
         * Only valid value is "depth" at the moment.
         */
        const std::string bufferType;

    public:
        unsigned int width;
        unsigned int height;

        /**
         * Constructor.
         */
        Renderbuffer(
            GraphicsContext& context,
            unsigned int initWidth = 1,
            unsigned int initHeight = 1,
            const std::string& initBufferType = "depth");

        /**
         * Constructs a new renderbuffer from an existing one.
         */
        Renderbuffer(const Renderbuffer& other);

        /**
         * Destructor.
         */
        ~Renderbuffer();

        /**
         * Resizes this framebuffer.
         */
        void resize(unsigned int width, unsigned int height);
    };
}

#endif
