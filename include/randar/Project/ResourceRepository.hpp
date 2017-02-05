#ifndef RANDAR_RESOURCE_RESOURCE_REPOSITORY_HPP
#define RANDAR_RESOURCE_RESOURCE_REPOSITORY_HPP

#include <cstdint>
#include <randar/Utility/Map.hpp>

namespace randar
{
    class Texture;
    class Model;

    class ResourceRepository
    {
        std::map<uint32_t, Model*> models;
        std::map<uint32_t, Texture*> textures;

    public:
        /**
         * Retrieves and adds a model.
         */
        Model* getModel(uint32_t id);
        uint32_t addModel(Model* model);

        /**
         * Retrieves and adds a texture.
         */
        Texture* getTexture(uint32_t id);
        uint32_t addTexture(Texture* texture);
    };
}

#endif
