#ifndef RANDAR_RENDER_LIGHT_SPOTLIGHT_HPP
#define RANDAR_RENDER_LIGHT_SPOTLIGHT_HPP

#include <randar/Render/Light/BaseLight.hpp>

namespace randar
{
    class Spotlight : public BaseLight
    {
    public:
        /**
         * Constructor.
         */
        Spotlight(GraphicsContext& context);

        /**
         * Generates the lightmap of a world.
         */
        virtual void generateMap(randar::World& world) override;
    };
}

#endif
