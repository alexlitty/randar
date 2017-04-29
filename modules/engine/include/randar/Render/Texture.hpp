#ifndef RANDAR_RENDER_TEXTURE_HPP
#define RANDAR_RENDER_TEXTURE_HPP

#define RANDAR_TEXTURE_MAX_WIDTH  4096
#define RANDAR_TEXTURE_MAX_HEIGHT 4096

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
         * Reads the contents of the texture.
         */
        void read(Image& image);
    };
}

#endif
