#include <randar/Render/Image.hpp>

// Default constructor.
randar::Image::Image()
: data(nullptr)
{

}

// Destructor.
randar::Image::~Image()
{
    this->freeData();
}

// Frees the raw image data.
void randar::Image::freeData()
{
    if (this->data) {
        delete[] this->data;
    }
}

// Allocates enough memory to accommodate the current image dimensions.
void randar::Image::allocateData()
{
    this->data = new float[this->rawSize()];
}

// Resizes the image.
void randar::Image::resize(uint32_t newWidth, uint32_t newHeight)
{
    if (this->getWidth() == newWidth && this->getHeight() == newHeight) {
        return;
    }

    this->freeData();
    randar::Dimensional2<uint32_t>::resize(newWidth, newHeight);
    this->allocateData();
}

// Gets the underlying buffer position for a pixel.
uint32_t randar::Image::getPixelIndex(const randar::Vector2<uint32_t>& vec) const
{
    return this->getPixelIndex(vec.x, vec.y);
}

uint32_t randar::Image::getPixelIndex(uint32_t x, uint32_t y) const
{
    return ((y * this->getWidth()) + (x)) * 4;
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

// Retrieves a pointer to the raw image data.
float* randar::Image::raw()
{
    return this->data;
}

// Retrieves the expected size of the raw image data.
uint32_t randar::Image::rawSize() const
{
    return this->getWidth() * this->getHeight() * 4;
}
