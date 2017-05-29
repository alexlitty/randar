#ifndef RANDAR_RENDER_SHAPE_HPP
#define RANDAR_RENDER_SHAPE_HPP

#include <randar/Render/Geometry.hpp>
#include <randar/Render/Palette/DefaultPalette.hpp>

/**
 * Helper methods to generate geometry.
 */
namespace randar
{
    Geometry sphere(float radius);
    Geometry cuboid(
        float width,
        float height,
        float depth,
        const Palette& palette = randar::defaultPalette);
}

#endif
