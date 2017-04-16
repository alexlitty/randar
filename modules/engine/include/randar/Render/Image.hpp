#ifndef RANDAR_RENDER_IMAGE_HPP
#define RANDAR_RENDER_IMAGE_HPP

#include <vector>
#include <randar/Math/Dimensional2.hpp>
#include <randar/Render/Color.hpp>

namespace randar
{
    class Image : public Dimensional2<uint32_t>
    {
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

    public:
        /**
         * Default constructor.
         *
         * Creates an empty image with no width nor height.
         */
        Image();

        /**
         * Destructor.
         */
        ~Image();

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
         * Resizes the image.
         *
         * If the image is decreasing in size, right-bottom pixels are
         * truncated. If increasing, the new area is filled with opaque black.
         *
         * It is more efficient to use the set method when an external buffer of
         * pixels is immediately available.
         *
         * @@@ todo - Image gets cleared upon resizing.
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
         *
         * If values always meet these requirements beforehand, use _setPixel.
         */
        void setPixel(const Vector2<uint32_t>& vec, const Color& color);
        void setPixel(uint32_t x, uint32_t y, const Color& color);
        void setPixel(uint32_t x, uint32_t y, float r, float g, float b, float a);

        /**
         * Blindly sets the color of a pixel.
         *
         * If the desired pixel is out of range or color values are not clamped
         * within [0, 1], behavior is undefined.
         *
         * If values may not meet these requirements beforehand, use setPixel.
         */
        void _setPixel(uint32_t x, uint32_t y, float r, float g, float b, float a);

        /**
         * Retrieves a pointer to the raw image data.
         */
        float* raw();

        /**
         * Retrieves the expected element size of the raw array.
         */
        uint32_t rawSize();
    };
}

#endif
