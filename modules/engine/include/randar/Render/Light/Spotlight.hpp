#ifndef RANDAR_RENDER_LIGHT_SPOTLIGHT_HPP
#define RANDAR_RENDER_LIGHT_SPOTLIGHT_HPP

#include <randar/Render/Light/BaseLight.hpp>

namespace randar
{
    class Spotlight : public BaseLight
    {
    public:
        /**
         * Default context constructor.
         */
        Spotlight();

        /**
         * Primary constructor.
         */
        Spotlight(GraphicsContext& context);

        /**
         * Sets and retrieves position.
         */
        void position(const Vector3& newPosition);
        void move(const Vector3& movement);
        Vector3 position();

        /**
         * Sets and retrieves the target vector.
         */
        void target(const Vector3& newTarget);
        Vector3 target();

        /**
         * Sets light range.
         */
        void range(float near, float far);

        /**
         * Generates the lightmap of a world.
         */
        virtual void generateMap(randar::World& world) override;
    };
}

#endif
