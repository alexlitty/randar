#ifndef RANDAR_RENDER_TEXTURE_HPP
#define RANDAR_RENDER_TEXTURE_HPP

#include <randar/Render/Image.hpp>
#include <randar/System/GlNamedResource.hpp>
#include <randar/System/GraphicsContextResource.hpp>

namespace randar
{
    class Texture :
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
         * Type of texture.
         *
         * Valid values are "rgba" and "depth".
         */
        const std::string type;

        /**
         * Disable assignment.
         */
        Texture(const Texture& other) = delete;
        Texture& operator =(const Texture& other) = delete;

        /**
         * Default context constructor.
         */
        Texture(
            uint32_t initWidth,
            uint32_t initHeight,
            const std::string& initType = "rgba");

        /**
         * Primary constructor.
         */
        Texture(
            GraphicsContext& context,
            uint32_t initWidth,
            uint32_t initHeight,
            const std::string& initType = "rgba");

        /**
         * Destructor.
         */
        virtual ~Texture();

        /**
         * Initializes the texture on the associated graphics context.
         */
        virtual void initialize();

        /**
         * Uninitializes the texture from the associated graphics context.
         */
        virtual void uninitialize();

        /**
         * Checks if the texture is initialized.
         */
        virtual bool isInitialized() const;

        /**
         * Binds the texture for further operations.
         */
        void bind();

        /**
         * Sets the texture as active for further operations.
         *
         * Internal use only.
         */
        void active(uint16_t index);

        /**
         * Resets the texture with arbitrary data.
         *
         * Implicitly lets the GPU know the current size of the texture.
         */
        void reset();

        /**
         * Resizes this texture.
         */
        virtual void resize(uint32_t newWidth, uint32_t newHeight) override;

        /**
         * Retrieves an image of the texture.
         */
        Image image();
    };
}

#endif
