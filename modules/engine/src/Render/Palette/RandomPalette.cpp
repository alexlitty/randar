#include <randar/Render/Palette/RandomPalette.hpp>

// Destructor.
randar::RandomPalette::~RandomPalette()
{

}

// Samples a completely random color.
randar::Color randar::RandomPalette::color() const
{
    return randar::randomColor();
}
