#include <randar/Project/ResourceRepository.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Render/Texture.hpp>

// Constructor.
randar::ResourceRepository::ResourceRepository()
{

}

// Dummy copy constructor.
randar::ResourceRepository::ResourceRepository(const randar::ResourceRepository& other)
{
    *this = other;
}

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

// Applies a resource patch to this repository.
void randar::ResourceRepository::apply(const randar::ResourcePatch& patch)
{
    if (patch.type == "textures") {
        this->getTexture(patch.id)->patch(patch.json);
    }
}

// Saves this repository to disk.
void randar::ResourceRepository::save()
{
    this->save(this->directory);
}

void randar::ResourceRepository::save(const randar::Directory& directory)
{
    for (auto item : this->models) {
        if (item.second->isDirty()) {
            this->exportRaModel(item.first);
        }
    }
}

// Retrieves a scene.
randar::Scene* randar::ResourceRepository::getScene(uint32_t id)
{
    return this->scenes[id];
}

// Adds a scene.
uint32_t randar::ResourceRepository::addScene(randar::Scene* scene)
{
    uint32_t key = randar::insertAtAvailableKey(this->scenes, scene);
    scene->id.set(key);
    return key;
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

    result["textures"] = randar::toJson(this->textures);
    result["models"] = randar::toJson(this->models);
    result["scenes"] = randar::toJson(this->scenes);

    return result;
}

// Assignment operator.
randar::ResourceRepository& randar::ResourceRepository::operator =(const randar::ResourceRepository& other)
{
    throw std::runtime_error("ResourceRepository is not copyable.");
    return *this;
}
