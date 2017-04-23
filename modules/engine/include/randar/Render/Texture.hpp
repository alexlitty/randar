#ifndef RANDAR_RENDER_TEXTURE_HPP
#define RANDAR_RENDER_TEXTURE_HPP

#define RANDAR_TEXTURE_MAX_WIDTH  4096
#define RANDAR_TEXTURE_MAX_HEIGHT 4096

#include <randar/Engine/GpuResource.hpp>
#include <randar/Render/Image.hpp>
#include <randar/System/GraphicsContext.hpp>

namespace randar
{
    class Texture : virtual public GpuResource, public Dimensional2<uint32_t>
    {
    public:
        /**
         * Type of texture.
         *
         * Valid values are "rgba" and "depth".
         */
        const std::string type;

        /**
         * New texture constructor.
         */
        Texture(
            GraphicsContext& context,
            uint32_t initWidth,
            uint32_t initHeight,
            const std::string& initType = "rgba");

        /**
         * Destructor.
         */
        ~Texture();

        /**
         * Binds the texture for further operations.
         */
        void bind();

        /**
         * Resets the texture with arbitrary data.
         *
         * Implicitly lets the GPU know the current size of the texture.
         */
        void reset();

        /**
         * Resizes this texture.
         */
        void resize(uint32_t width, uint32_t height);
    };
}

#endif
