#ifndef RANDAR_SCENE_SCENE_HPP
#define RANDAR_SCENE_SCENE_HPP

#ifdef RANDAR_IGNORE

#include <randar/Engine/Resource.hpp>
#include <randar/Scene/Object.hpp>

namespace randar
{
    class Scene : virtual public Resource
    {
    public:
        /**
         * The desired frames per second in this scene.
         */
        uint16_t fps = 24;

        /**
         * The models used in this scene.
         */
        std::map<uint32_t, Object*> objects;

        /**
         * Destructor.
         */
        ~Scene();

        /**
         * Retrieves scene data as JSON.
         */
        Json toJson() const;
    };
}

#endif

#endif
