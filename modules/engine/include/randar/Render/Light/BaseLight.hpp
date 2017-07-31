#ifndef RANDAR_RENDER_LIGHT_BASE_LIGHT_HPP
#define RANDAR_RENDER_LIGHT_BASE_LIGHT_HPP

#include <randar/Render/Framebuffer.hpp>

namespace randar
{
    class BaseLight : public GraphicsContextResource, public Transform
    {
    protected:
        Framebuffer framebuffer;
        Texture map;

    public:
        /**
         * Disable assignment.
         */
        BaseLight(const BaseLight& other) = delete;
        BaseLight& operator=(const BaseLight& other) = delete;

        /**
         * Constructor.
         */
        BaseLight(GraphicsContext& context);

        /**
         * Generates and returns the light's map.
         */
        virtual Texture& lightmap(randar::World& world) = 0;

        /**
         * Returns the MVP matrix being used by the light.
         */
        virtual glm::mat4 matrix();
    };
}

#endif
