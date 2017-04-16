#include <randar/Render/Image.hpp>

// Default constructor.
randar::Image::Image()
{

}

// Resizes the image.
void randar::Image::resize(uint32_t newWidth, uint32_t newHeight)
{
    if (this->getWidth() == newWidth && this->getHeight() == newHeight) {
        return;
    }

    this->data.resize(newWidth * newHeight * 4);
    randar::Dimensional2<uint32_t>::resize(newWidth, newHeight);
}

// Gets the underlying buffer position for a pixel.
uint32_t randar::Image::getPixelIndex(const randar::Vector2<uint32_t>& vec) const
{
    return this->getPixelIndex(vec.x, vec.y);
}

uint32_t randar::Image::getPixelIndex(uint32_t x, uint32_t y) const
{
    return ((y * getWidth()) + (x)) * 4;
}

// Gets the color of a pixel.
randar::Color randar::Image::getPixel(const randar::Vector2<uint32_t>& vec) const
{
    return this->getPixel(vec.x, vec.y);
}

randar::Color randar::Image::getPixel(uint32_t x, uint32_t y) const
{
    uint32_t index = this->getPixelIndex(x, y);
    return randar::Color(
        this->data[index++],
        this->data[index++],
        this->data[index++],
        this->data[index++]
    );
}

// Safely sets the color of a pixel.
void randar::Image::setPixel(const randar::Vector2<uint32_t>& vec, const randar::Color& color)
{
    this->setPixel(vec.x, vec.y, color);
}

void randar::Image::setPixel(uint32_t x, uint32_t y, const randar::Color& color)
{
    if (!this->isWithinDimensions(x, y)) {
        return;
    }
    this->_setPixel(x, y, color.r(), color.g(), color.b(), color.a());
}

void randar::Image::setPixel(uint32_t x, uint32_t y, float r, float g, float b, float a)
{
    this->setPixel(x, y, Color(r, g, b, a));
}

// Blindly sets the color of a pixel.
void randar::Image::_setPixel(uint32_t x, uint32_t y, float r, float g, float b, float a)
{
    uint32_t index = this->getPixelIndex(x, y);
    this->data[index++] = r;
    this->data[index++] = g;
    this->data[index++] = b;
    this->data[index++] = a;
}

// Retrieves a read-only reference to the raw image data.
const std::vector<float>& randar::Image::getData()
{
    return this->data;
}
