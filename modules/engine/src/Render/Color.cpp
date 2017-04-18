#include <randar/Math/Random.hpp>
#include <randar/Render/Color.hpp>
#include <randar/Utility/Clamp.hpp>

// Default constructor.
randar::Color::Color()
: randar::Color::Color(0.0f, 0.0f, 0.0f)
{

}

// Primary constructor.
randar::Color::Color(float rInit, float gInit, float bInit, float aInit)
{
    this->set(rInit, gInit,  bInit, aInit);
}

// Safely sets the color using float values.
void randar::Color::set(float rNew, float gNew, float bNew, float aNew)
{
    this->r(rNew);
    this->g(gNew);
    this->b(bNew);
    this->a(aNew);
}

// Safely sets a channel on the color using float values.
void randar::Color::r(float v)
{
    this->_r(randar::clampUnsignedFloat(v));
}

void randar::Color::g(float v)
{
    this->_g(randar::clampUnsignedFloat(v));
}

void randar::Color::b(float v)
{
    this->_b(randar::clampUnsignedFloat(v));
}

void randar::Color::a(float v)
{
    this->_a(randar::clampUnsignedFloat(v));
}

// Sets the color using 8-bit integer values.
void randar::Color::setInt(uint8_t rNew, uint8_t gNew, uint8_t bNew, uint8_t aNew)
{
    this->rInt(rNew);
    this->bInt(bNew);
    this->gInt(gNew);
    this->aInt(aNew);
}

// Sets a channel on the color using 8-bit integer values.
void randar::Color::rInt(uint8_t v)
{
    this->_r(v / 255.0f);
}

void randar::Color::gInt(uint8_t v)
{
    this->_g(v / 255.0f);
}

void randar::Color::bInt(uint8_t v)
{
    this->_b(v / 255.0f);
}

void randar::Color::aInt(uint8_t v)
{
    this->_a(v / 255.0f);
}

// Gets a channel on the color as a float clamped within [0, 1].
float randar::Color::r() const
{
    return this->data[0];
}

float randar::Color::g() const
{
    return this->data[1];
}

float randar::Color::b() const
{
    return this->data[2];
}

float randar::Color::a() const
{
    return this->data[3];
}

// Gets a channel on the color as an 8-bit integer.
uint8_t randar::Color::rInt() const
{
    return this->r() * 255.0f;
}

uint8_t randar::Color::gInt() const
{
    return this->g() * 255.0f;
}

uint8_t randar::Color::bInt() const
{
    return this->b() * 255.0f;
}

uint8_t randar::Color::aInt() const
{
    return this->a() * 255.0f;
}

// Randomizes the red, green, and blue channels in this color.
void randar::Color::randomize(bool randomizeAlpha)
{
    this->rInt(randar::randomFloat());
    this->gInt(randar::randomFloat());
    this->bInt(randar::randomFloat());
    this->aInt(randar::randomFloat());
}

// Generates a random color with full opacity.
randar::Color randar::randomColor()
{
    Color color;
    color.randomize();
    return color;
}
