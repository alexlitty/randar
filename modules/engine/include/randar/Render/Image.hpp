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
         * red, green, blue, and alpha values respectively from 0 to 1.
         *
         * First pixel is the top-left corner of the image.
         */
        std::vector<float> data;

    public:
        /**
         * Default constructor.
         *
         * Creates an empty image with no width nor height.
         */
        Image();

        /**
         * Resizes the image.
         *
         * If the image is decreasing in size, right-bottom pixels are
         * truncated. If increasing, the new area is filled with black pixels.
         *
         * It is more efficient to use the set method when an external buffer of
         * pixels is immediately available.
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
        uint32_t getPixelIndex(const Vector2<uint32_t>& vec);
        uint32_t getPixelIndex(uint32_t x, uint32_t y);

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
         * Retrieves a read-only reference to the raw image data.
         */
        const std::vector<float>& getData();
    };
}

#endif
