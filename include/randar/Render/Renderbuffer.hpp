#ifndef RANDAR_RENDER_RENDERBUFFER_HPP
#define RANDAR_RENDER_RENDERBUFFER_HPP

#include <randar/Engine/GpuResource.hpp>

namespace randar
{
    struct Renderbuffer : virtual public GpuResource
    {
        enum Type {
            INVALID,
            DEPTH
        };

        const Type type;
        unsigned int width;
        unsigned int height;

        /**
         * Constructor.
         */
        Renderbuffer(
            Type initType = Renderbuffer::Type::INVALID,
            unsigned int initWidth = 1,
            unsigned int initHeight = 1);

        /**
         * Resizes this framebuffer.
         */
        void resize(unsigned int width, unsigned int height);

        /**
         * Resource initialization and destruction.
         */
        virtual void initialize() override;
        virtual void destroy() override;
    };
}

#endif
