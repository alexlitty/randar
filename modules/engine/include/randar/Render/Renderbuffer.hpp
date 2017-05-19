#ifndef RANDAR_RENDER_RENDERBUFFER_HPP
#define RANDAR_RENDER_RENDERBUFFER_HPP

#include <randar/Math/Dimensional2.hpp>
#include <randar/System/GlNamedResource.hpp>
#include <randar/System/GraphicsContextResource.hpp>

namespace randar
{
    class Renderbuffer :
        virtual public GraphicsContextResource,
        virtual public GlNamedResource,
        virtual public Dimensional2<uint32_t>
    {
    public:
        /**
         * Help swig identify inherited methods.
         */
        using Dimensional2<uint32_t>::getWidth;
        using Dimensional2<uint32_t>::getHeight;
        using Dimensional2<uint32_t>::setWidth;
        using Dimensional2<uint32_t>::setHeight;
        using Dimensional2<uint32_t>::hasDimensions;
        using Dimensional2<uint32_t>::isWithinDimensions;

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
        virtual void resize(uint32_t newWidth, uint32_t newHeight) override;
    };
}

#endif
