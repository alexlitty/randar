#ifndef RANDAR_SCENE_SCENE_HPP
#define RANDAR_SCENE_SCENE_HPP

#include <randar/Scene/SceneModel.hpp>

namespace randar
{
    class Scene
    {
        /**
         * The desired frames per second in this scene.
         */
        uint16_t fps;

        /**
         * The models used in this scene.
         */
        std::map<uint32_t, SceneModel*> models;

        /**
         * Destructor.
         */
        ~Scene();
    };
}

#endif
