#include <randar/Math/Random.hpp>
#include <randar/Render/Palette/VaryingPalette.hpp>

// Constructor.
randar::VaryingPalette::VaryingPalette(
    const randar::Color& initBase,
    const randar::Color& initVary)
: base(initBase),
  vary(initVary)
{

}

// Destructor.
randar::VaryingPalette::~VaryingPalette()
{

}

// Samples a color from the palette.
randar::Color randar::VaryingPalette::color() const
{
    return base.varied(this->vary);
}

// Node.js helper.
randar::VaryingPalette randar::varyingPalette(
    const randar::Color& base,
    const randar::Color& vary)
{
    return randar::VaryingPalette(base, vary);
}
