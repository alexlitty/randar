#include <randar/Project/ResourceRepository.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Render/Texture.hpp>

// Retrieves a model.
randar::Model* randar::ResourceRepository::getModel(uint32_t id)
{
    return this->models[id];
}

// Adds a model.
uint32_t randar::ResourceRepository::addModel(randar::Model* model)
{
    return randar::insertAtAvailableKey(this->models, model);
}

// Retrieves a texture.
randar::Texture* randar::ResourceRepository::getTexture(uint32_t id)
{
    return this->textures[id];
}

// Adds a texture.
uint32_t randar::ResourceRepository::addTexture(randar::Texture* texture)
{
    return randar::insertAtAvailableKey(this->textures, texture);
}
