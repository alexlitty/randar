#ifndef RANDAR_PROJECT_RESOURCE_REPOSITORY_HPP
#define RANDAR_PROJECT_RESOURCE_REPOSITORY_HPP

#include <cstdint>
#include <set>
#include <randar/Engine/Gpu.hpp>
#include <randar/Filesystem/Directory.hpp>
#include <randar/Render/Texture.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Scene/Scene.hpp>
#include <randar/Project/ResourcePatch.hpp>
#include <randar/Utility/Map.hpp>
#include <randar/Utility/Json.hpp>

namespace randar
{
    class ResourceRepository
    {
        Gpu& gpu = randar::getDefaultGpu();

        /**
         * The location of this repository on disk.
         */
        Directory directory;

    public:
        /**
         * Resources in this repository.
         */
        std::map<uint32_t, Scene*> scenes;
        std::map<uint32_t, Model*> models;
        std::map<uint32_t, Texture*> textures;

        /**
         * Constructor.
         */
        ResourceRepository();

        /**
         * Dummy copy constructor.
         */
        ResourceRepository(const ResourceRepository& other);

        /**
         * Destructor.
         */
        ~ResourceRepository();

        /**
         * Frees this repository from memory.
         */
        void clear();

        /**
         * Loads a repository from disk.
         *
         * An exception is thrown upon error.
         */
        void load(const Directory& directory);

        /**
         * Applies a resource patch to this repository.
         */
        void apply(const ResourcePatch& patch);

        /**
         * Saves this repository to disk.
         *
         * An exception is thrown upon error.
         */
        void save();
        void save(const Directory& directory);

        /**
         * Retrieves and adds a scene.
         */
        Scene* getScene(uint32_t id);
        uint32_t addScene(Scene* scene);

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

        /**
         * Texture importing and exporting.
         */
        void importRaTexture(const File& file);
        void importPng(const File& file);

        void exportRaTexture(uint32_t textureId);

        /**
         * Model importing and exporting.
         */
        void importRaModel(const File& file);
        void importIqm(const File& file);

        void exportRaModel(uint32_t modelId);

        /**
         * Generates a complete JSON representation of this repository.
         */
        Json toJson() const;

        /**
         * Assignment operator.
         */
        ResourceRepository& operator =(const ResourceRepository& other);
    };
}

#ifdef SWIG
    %template(map_model) std::map<uint32_t, randar::Model*>;
    %template(map_scene) std::map<uint32_t, randar::Scene*>;
    %template(map_texture) std::map<uint32_t, randar::Texture*>;
#endif

#endif
