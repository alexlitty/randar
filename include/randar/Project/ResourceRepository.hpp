#ifndef RANDAR_RESOURCE_RESOURCE_REPOSITORY_HPP
#define RANDAR_RESOURCE_RESOURCE_REPOSITORY_HPP

#include <cstdint>
#include <set>
#include <randar/Engine/Gpu.hpp>
#include <randar/Filesystem/Directory.hpp>
#include <randar/Render/Texture.hpp>
#include <randar/Render/Model.hpp>
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

        /**
         * Resources in this repository.
         */
        std::map<uint32_t, Model*> models;
        std::set<uint32_t> dirtyModels;

        std::map<uint32_t, Texture*> textures;
        std::set<uint32_t> dirtyTextures;

    public:
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
         * Saves this repository to disk.
         *
         * An exception is thrown upon error.
         */
        void save();
        void save(const Directory& directory);

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
        void importIqm(const File& file);

        /**
         * Generates a complete JSON representation of this repository.
         */
        Json toJson() const;
    };
}

#endif
