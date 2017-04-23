#ifndef RANDAR_RENDER_RENDERBUFFER_HPP
#define RANDAR_RENDER_RENDERBUFFER_HPP

#include <randar/Engine/GpuResource.hpp>
#include <randar/System/GraphicsContext.hpp>

namespace randar
{
    class Renderbuffer : public GpuResource, virtual Dimensional2<uint32_t>
    {
    public:
        /**
         * Type of renderbuffer.
         *
         * Only valid value is "depth" at the moment.
         */
        const std::string bufferType;

        /**
         * Constructor.
         */
        Renderbuffer(
            GraphicsContext& context,
            uint32_t initWidth,
            uint32_t initHeight,
            const std::string& initBufferType = "depth");

        /**
         * Disable assignment.
         */
        Renderbuffer(const Renderbuffer& other) = delete;
        Renderbuffer& operator =(const Renderbuffer& other) = delete;

        /**
         * Destructor.
         */
        ~Renderbuffer();

        /**
         * Binds the renderbuffer for further operations.
         */
        void bind();

        /**
         * Resizes this framebuffer.
         */
        void resize(uint32_t newWidth, uint32_t newHeight);
    };
}

#endif
