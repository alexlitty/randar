#include <stdexcept>
#include <randar/Render/Image.hpp>

// Default constructor.
randar::Image::Image()
: data(nullptr)
{

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
        this->data = new float[this->rawSize()];
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
    if (!this->hasDimensions()) {
        throw std::runtime_error("Image has no dimensions");
    }

    if (x >= this->getWidth() || y >= this->getHeight()) {
        throw std::runtime_error("Pixel position out of range");
    }

    if (this->internalLayout == Image::LAYOUT::FLIP_VERTICAL) {
        return ((((this->getHeight() - 1) - y) * this->getWidth()) + x) * 4;
    } else {
        return ((y * this->getWidth()) + x) * 4;
    }
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
    this->data[index] = r;
    this->data[index + 1] = g;
    this->data[index + 2] = b;
    this->data[index + 3] = a;
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

// Assignment operator.
randar::Image& randar::Image::operator =(const randar::Image& other)
{
    this->resize(other.getWidth(), other.getHeight());

    for (uint32_t x = 0; x < this->getWidth(); x++) {
        for (uint32_t y = 0; y < this->getHeight(); y++) {
            this->setPixel(x, y, other.getPixel(x, y));
        }
    }

    return *this;
}
