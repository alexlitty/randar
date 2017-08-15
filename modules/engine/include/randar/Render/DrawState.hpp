#ifndef RANDAR_RENDER_DRAW_STATE_HPP
#define RANDAR_RENDER_DRAW_STATE_HPP

#include <randar/Render/Model.hpp>
#include <randar/Render/TextureCollection.hpp>

namespace randar
{
    class BaseLight;
    typedef std::vector<BaseLight*> LightCollection;

    /**
     * State object for fine geometry drawing control.
     *
     * Passed into canvas drawing methods. Null properties are substituted with
     * defaults.
     */
    struct DrawState
    {
        Transform* transform;
        Skeleton* skeleton;
        TextureCollection* textures;
        LightCollection* lights;
        ShaderProgram* program;

        /**
         * Constructor.
         */
        DrawState();
    };
}

#endif
