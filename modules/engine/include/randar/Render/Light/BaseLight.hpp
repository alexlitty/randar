#ifndef RANDAR_RENDER_LIGHT_BASE_LIGHT_HPP
#define RANDAR_RENDER_LIGHT_BASE_LIGHT_HPP

#include <randar/Render/Framebuffer.hpp>

namespace randar
{
    class BaseLight : public GraphicsContextResource
    {
    protected:
        Framebuffer framebuffer;
        Texture lightmap;

    public:
        /**
         * Disable assignment.
         */
        BaseLight(const BaseLight& other) = delete;
        BaseLight& operator=(const BaseLight& other) = delete;

        /**
         * Default context constructor.
         */
        BaseLight();

        /**
         * Primary constructor.
         */
        BaseLight(GraphicsContext& context);

        /**
         * Generates the lightmap of a world.
         */
        virtual void generateMap(randar::World& world) = 0;

        /**
         * Returns the latest lightmap.
         */
        virtual Texture& map();

        /**
         * Returns the MVP matrix being used by the light.
         *
         * Includes a bias matrix that converts to texture coordinates.
         */
        virtual glm::mat4 matrix();
    };
}

#endif
