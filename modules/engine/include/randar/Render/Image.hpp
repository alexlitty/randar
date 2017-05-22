#ifndef RANDAR_RENDER_IMAGE_HPP
#define RANDAR_RENDER_IMAGE_HPP

#include <vector>
#include <randar/Math/Dimensional2.hpp>
#include <randar/Render/Color.hpp>

namespace randar
{
    class Image : virtual public Dimensional2<uint32_t>
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
         * A description of an image's pixel layout.
         */
        enum class LAYOUT
        {
            // Pixels are left-to-right, starting from top-left.
            NORMAL,

            // Pixels are left-to-right, starting from bottom-left.
            FLIP_VERTICAL
        };

    protected:
        /**
         * Raw image data.
         *
         * Each pixel is represented by four consecutive floats indicating the
         * red, green, blue, and alpha values clamped within [0, 1].
         *
         * First pixel is the top-left corner of the image.
         */
        float* data;

        /**
         * Pixel layout of the raw image data.
         */
        LAYOUT internalLayout = LAYOUT::NORMAL;

    public:
        /**
         * Default constructor.
         *
         * Creates an empty image with no width nor height.
         */
        Image();

        /**
         * Primary constructor.
         */
        Image(uint32_t initWidth, uint32_t initHeight);

        /**
         * Copy constructor.
         */
        Image(const Image& other);

        /**
         * Destructor.
         */
        ~Image();

        /**
         * Assignment operator.
         */
        Image& operator =(const Image& other);

        /**
         * Copies a data buffer into the image.
         */
        void copy(float* otherData, uint32_t newWidth, uint32_t newHeight);

        /**
         * Adopts an externally created data buffer.
         */
        void adopt(float* newData, uint32_t newWidth, uint32_t newHeight);

    protected:
        /**
         * Frees the raw image data.
         */
        void freeData();

        /**
         * Allocates enough memory to accommodate the current image dimensions.
         *
         * Any previous data is not freed.
         */
        void allocateData();

    public:
        /**
         * Sets and retrieves the internal data layout.
         */
        void layout(LAYOUT newLayout);
        LAYOUT layout() const;

        /**
         * Resizes the image.
         *
         * The image's data is reallocated. Any existing data is lost.
         */
        virtual void resize(uint32_t newWidth, uint32_t newHeight) override;

        /**
         * Gets the underlying buffer position for the beginning of a pixel.
         *
         * This is primarily used internally, but exposed for external objects
         * that would like to use the underlying buffer.
         *
         * The position should be checked beforehand to ensure it is within the
         * image's range. If it is out of a range, behavior is undefined.
         */
        uint32_t getPixelIndex(const Vector2<uint32_t>& vec) const;
        uint32_t getPixelIndex(uint32_t x, uint32_t y) const;

        /**
         * Gets the color of a pixel.
         *
         * If the desired pixel is out of range, behavior is undefined.
         */
        Color getPixel(const Vector2<uint32_t>& vec) const;
        Color getPixel(uint32_t x, uint32_t y) const;

        /**
         * Safely sets the color of a pixel.
         *
         * Positions begin at 0. If the desired pixel is out of range, nothing
         * happens. Color values are clamped within [0, 1].
         */
        void setPixel(const Vector2<uint32_t>& vec, const Color& color);
        void setPixel(const Vector2<uint32_t>& vec,  float r, float g, float b, float a = 1.0f);
        void setPixel(uint32_t x, uint32_t y, const Color& color);
        void setPixel(uint32_t x, uint32_t y, float r, float g, float b, float a = 1.0f);

        /**
         * Retrieves a pointer to the raw image data.
         */
        float* raw();
        const float* raw() const;

        /**
         * Calculates the expected element count of the raw image data.
         */
        uint32_t rawCount() const;

        /**
         * Calculates the expected byte size of the raw image data.
         */
        uint32_t rawSize() const;
    };

    /**
     * Node.js helpers for intuitive image creation.
     */
    Image image();
    Image image(uint32_t width, uint32_t height);
}

#endif
