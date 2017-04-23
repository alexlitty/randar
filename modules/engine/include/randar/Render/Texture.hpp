#ifndef RANDAR_RENDER_TEXTURE_HPP
#define RANDAR_RENDER_TEXTURE_HPP

#include <randar/Engine/GpuResource.hpp>
#include <randar/Math/Rect.hpp>
#include <randar/Math/Dimensional2.hpp>
#include <randar/Render/Color.hpp>

namespace randar
{
    class Texture : virtual public GpuResource, public Dimensional2<uint32_t>
    {
    protected:
        /**
         * Type of texture.
         *
         * Valid values are "rgba" and "depth".
         */
        std::string type;

        /**
         * Texture dimensions.
         */
        uint32_t width;
        uint32_t height;

    public:
        /**
         * Raw RGBA data.
         *
         * This data is not always available in memory. It is primarily used for
         * serializing and deserializing. This data is otherwise sent to the GPU
         * and freed from client memory.
         *
         * The first four elements are the red, green, blue, and alpha values
         * for the bottom-left pixel. The second set of elements are for the
         * next pixel in the row, and so on, looping around to the rows above.
         */
        std::vector<uint8_t> data;

        /**
         * New texture constructor.
         */
        Texture(
            Gpu* gpuInit,
            std::string initType,
            uint32_t initWidth,
            uint32_t initHeight);

        /**
         * Destructor.
         */
        ~Texture();

        /**
         * Binds the texture for further operations.
         */
        void bind();

        /**
         * Saves this texture to its file.
         */
        virtual bool save();

        /**
         * Checks the validity of this texture's information.
         *
         * Does not check GPU validity.
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
