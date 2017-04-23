#ifndef RANDAR_RENDER_TEXTURE_HPP
#define RANDAR_RENDER_TEXTURE_HPP

#include <randar/Engine/GpuResource.hpp>
#include <randar/Math/Rect.hpp>
#include <randar/Math/Dimensional2.hpp>
#include <randar/Render/Color.hpp>

#define RANDAR_TEXTURE_MAX_WIDTH  4096
#define RANDAR_TEXTURE_MAX_HEIGHT 4096

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
            Gpu* gpuInit,
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
