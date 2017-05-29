#ifndef RANDAR_RENDER_PALETTE_HPP
#define RANDAR_RENDER_PALETTE_HPP

#include <randar/Render/Color.hpp>

namespace randar
{
    /**
     * A color palette.
     *
     * Used to sample specifically random colors.
     */
    struct Palette
    {
        /**
         * Destructor.
         */
        virtual ~Palette();

        /**
         * Samples a color randomly from the palette.
         */
        virtual Color color() const = 0;
    };
}

#endif
