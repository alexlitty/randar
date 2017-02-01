#ifndef RANDAR_RENDER_TEXTURE_HPP
#define RANDAR_RENDER_TEXTURE_HPP

#include <randar/Engine/GpuResource.hpp>
#include <randar/Engine/FileResource.hpp>
#include <randar/Render/Color.hpp>

namespace randar
{
    class Texture : virtual public GpuResource, virtual public FileResource
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
            std::string initType,
            uint32_t initWidth,
            uint32_t initHeight,
            bool initialize = true);

        /**
         * Construct from a file.
         */
        Texture(const std::string& file);

        /**
         * Destructor.
         */
        ~Texture();

        /**
         * Saves this texture to its file.
         */
        virtual bool save() override;

        /**
         * Checks the validity of this texture's information.
         *
         * Does not check GPU validity.
         *
         * If the texture is invalid, the error argument is filled with a
         * description of the problem. Otherwise the argument remains unchanged.
         */
        bool isValid(std::string& error) const;

        /**
         * Checks which kind of texture this is.
         */
        bool isRgba() const;
        bool isDepth() const;

        /**
         * Clears this texture with a color.
         *
         * @todo - Inefficient.
         */
        void clear(const Color& color = Color(0.0f, 0.0f, 0.0f));
 
        /**
         * Resizes this texture.
         */
        void resize(unsigned int width, unsigned int height);

        /**
         * Retrieves the width and height of this texture.
         */
        unsigned int getWidth() const;
        unsigned int getHeight() const;

        /**
         * Converts this texture to a JSON representation.
         */
        virtual Json toJson() const override;
    };
}

#endif
