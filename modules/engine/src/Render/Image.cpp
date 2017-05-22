#include <cstring>
#include <stdexcept>
#include <randar/Render/Image.hpp>

// Default constructor.
randar::Image::Image()
: randar::Dimensional2<uint32_t>(0, 0),
  data(nullptr)
{

}

// Primary constructor.
randar::Image::Image(uint32_t initWidth, uint32_t initHeight)
: randar::Image()
{
    this->resize(initWidth, initHeight);
}

// Copy constructor.
randar::Image::Image(const randar::Image& other)
: randar::Image()
{
    *this = other;
}

// Destructor.
randar::Image::~Image()
{
    this->freeData();
}

// Assignment operator.
randar::Image& randar::Image::operator =(const randar::Image& other)
{
    this->copy(other.data, other.getWidth(), other.getHeight());
    this->internalLayout = other.internalLayout;
    return *this;
}

// Copies a data buffer into the image.
void randar::Image::copy(float* otherData, uint32_t newWidth, uint32_t newHeight)
{
    this->resize(newWidth, newHeight);

    if (this->data) {
        std::memcpy(this->data, otherData, this->rawSize());
    }
}

// Adopts an externally created data buffer.
void randar::Image::adopt(float* newData, uint32_t newWidth, uint32_t newHeight)
{
    this->freeData();

    this->width  = newWidth;
    this->height = newHeight;
    this->data = newData;
}

// Frees the raw image data.
void randar::Image::freeData()
{
    if (this->data) {
        delete[] this->data;
        this->data = nullptr;
    }
}

// Allocates enough memory to accommodate the current image dimensions.
void randar::Image::allocateData()
{
    if (!this->hasDimensions()) {
        this->data = nullptr;
    } else {
        this->data = new float[this->rawCount()];
    }
}

// Sets and retrieves the internal data layout.
void randar::Image::layout(randar::Image::LAYOUT newLayout)
{
    this->internalLayout = newLayout;
}

randar::Image::LAYOUT randar::Image::layout() const
{
    return this->internalLayout;
}

// Resizes the image.
void randar::Image::resize(uint32_t newWidth, uint32_t newHeight)
{
    Dimensional2<uint32_t>::resize(newWidth, newHeight);
    this->freeData();
    this->allocateData();
}

// Gets the underlying buffer position for a pixel.
uint32_t randar::Image::getPixelIndex(const randar::Vector2<uint32_t>& vec) const
{
    return this->getPixelIndex(vec.x, vec.y);
}

uint32_t randar::Image::getPixelIndex(uint32_t x, uint32_t y) const
{
    if (!this->hasDimensions()) {
        throw std::runtime_error("Image has no dimensions");
    }

    if (x >= this->getWidth() || y >= this->getHeight()) {
        throw std::runtime_error("Pixel position out of range");
    }

    if (this->internalLayout == Image::LAYOUT::FLIP_VERTICAL) {
        y = (this->getHeight() - y - 1);
    }

    return ((y * this->getWidth()) + x) * 4;
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
        this->data[index],
        this->data[index + 1],
        this->data[index + 2],
        this->data[index + 3]
    );
}

// Safely sets the color of a pixel.
void randar::Image::setPixel(const randar::Vector2<uint32_t>& vec, const randar::Color& color)
{
    this->setPixel(vec.x, vec.y, color);
}

void randar::Image::setPixel(const randar::Vector2<uint32_t>& vec, float r, float g, float b, float a)
{
    this->setPixel(vec, Color(r, g, b, a));
}

void randar::Image::setPixel(uint32_t x, uint32_t y, const randar::Color& color)
{
    uint32_t index = this->getPixelIndex(x, y);

    this->data[index]     = color.r();
    this->data[index + 1] = color.g();
    this->data[index + 2] = color.b();
    this->data[index + 3] = color.a();
}

void randar::Image::setPixel(uint32_t x, uint32_t y, float r, float g, float b, float a)
{
    this->setPixel(x, y, Color(r, g, b, a));
}

// Retrieves a pointer to the raw image data.
float* randar::Image::raw()
{
    return this->data;
}

const float* randar::Image::raw() const
{
    return this->data;
}

// Calculates the expected element count of the raw image data.
uint32_t randar::Image::rawCount() const
{
    return this->getWidth() * this->getHeight() * 4;
}

// Calculates the expected byte size of the raw image data.
uint32_t randar::Image::rawSize() const
{
    return this->rawCount() * sizeof(float);
}

// Node.js helpers for intuitive image creation.
randar::Image randar::image()
{
    return std::move(randar::Image());
}

randar::Image randar::image(uint32_t width, uint32_t height)
{
    return std::move(randar::Image(width, height));
}
