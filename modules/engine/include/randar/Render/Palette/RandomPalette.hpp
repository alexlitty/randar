#ifndef RANDAR_RENDER_RANDOM_PALETTE_HPP
#define RANDAR_RENDER_RANDOM_PALETTE_HPP

#include <randar/Render/Palette/Palette.hpp>

namespace randar
{
    struct RandomPalette : virtual public Palette
    {
        /**
         * Destructor.
         */
        virtual ~RandomPalette();

        /**
         * Samples a completely random color.
         */
        virtual Color color() const override;
    };

    /**
     * Node.js helper.
     */
    RandomPalette randomPalette();
}

#endif
