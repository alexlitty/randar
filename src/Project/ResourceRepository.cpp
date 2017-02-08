#include <randar/Project/ResourceRepository.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Render/Texture.hpp>

// Destructor.
randar::ResourceRepository::~ResourceRepository()
{
    this->clear();
}

// Frees this repository from memory.
void randar::ResourceRepository::clear()
{
    for (auto item : this->models) {
        delete item.second;
    }
    this->models.clear();

    for (auto item : this->textures) {
        delete item.second;
    }
    this->textures.clear();
}

// Loads a repository from disk.
void randar::ResourceRepository::load(const randar::Directory& directory)
{
    this->directory = directory;

    for (auto file : this->directory.getSubdirectory("textures").getFiles()) {
        this->importRaTexture(file);
    }

    for (auto file : this->directory.getSubdirectory("models").getFiles()) {
        this->importRaModel(file);
    }
}

// Saves this repository to disk.
void randar::ResourceRepository::save()
{
    this->save(this->directory);
}

void randar::ResourceRepository::save(const randar::Directory& directory)
{
    Directory dirTextures = directory.getSubdirectory("textures");

    for (auto item : this->textures) {
        this->exportRaTexture(item.first);
    }
}

// Retrieves a model.
randar::Model* randar::ResourceRepository::getModel(uint32_t id)
{
    return this->models[id];
}

// Adds a model.
uint32_t randar::ResourceRepository::addModel(randar::Model* model)
{
    uint32_t key = randar::insertAtAvailableKey(this->models, model);
    model->id.set(key);

    this->exportRaModel(key);
    return key;
}

// Retrieves a texture.
randar::Texture* randar::ResourceRepository::getTexture(uint32_t id)
{
    return this->textures[id];
}

// Adds a texture.
uint32_t randar::ResourceRepository::addTexture(randar::Texture* texture)
{
    uint32_t key = randar::insertAtAvailableKey(this->textures, texture);
    texture->id.set(key);

    this->exportRaTexture(key);
    return key;
}

// Generates a complete JSON representation of this repository.
Json randar::ResourceRepository::toJson() const
{
    Json result;

    for (auto item : this->textures) {
        result["textures"][item.first] = "test texture";
    }

    for (auto item : this->models) {
        result["models"][item.first] = "test model";
    }

    return result;
}
