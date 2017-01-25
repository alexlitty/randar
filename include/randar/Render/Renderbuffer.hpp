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
