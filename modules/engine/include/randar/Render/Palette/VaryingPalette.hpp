#ifndef RANDAR_RENDER_VARYING_PALETTE_HPP
#define RANDAR_RENDER_VARYING_PALETTE_HPP

#include <randar/Render/Palette/Palette.hpp>

namespace randar
{
    struct VaryingPalette : virtual public Palette
    {
        /**
         * Base color of the palette.
         */
        Color base;

        /**
         * How much the base color should vary.
         */
        Color vary;

        /**
         * Constructor.
         */
        VaryingPalette(const Color& initBase, const Color& initVary);

        /**
         * Destructor.
         */
        virtual ~VaryingPalette();

        /**
         * Samples a color from the palette.
         */
        virtual Color color() const override;
    };

    /**
     * Node.js helper.
     */
    VaryingPalette varyingPalette(const Color& base, const Color& vary);
}

#endif
