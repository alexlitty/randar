#ifndef RANDAR_ENGINE_PROJECT_HPP
#define RANDAR_ENGINE_PROJECT_HPP

#include <randar/Render/ShaderProgram.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Utility/File.hpp>
#include <randar/Utility/Json.hpp>
#include <randar/Utility/Map.hpp>

namespace randar
{
    class Project
    {
        std::string directory;

    public:
        std::string name;
        std::map<std::string, ShaderProgram*> shaderPrograms;
        std::map<std::string, Texture*> textures;
        std::map<std::string, Model*> models;

        /**
         * Default constructor.
         */
        Project();

        /**
         * Copy constructor.
         */
        Project(const Project& other);

        /**
         * Destructor.
         */
        ~Project();

    protected:
        /**
         * Retrieves the filename of the primary project file.
         */
        std::string getProjectFilename() const;

    public:
        /**
         * Loads a project into memory, given a project directory.
         *
         * Returns true if the project was loaded successfully, false otherwise.
         */
        bool load(const std::string& directory);

        /**
         * Saves this project to disk.
         *
         * Returns true if the project was saved successfully, false otherwise.
         */
        bool save() const;

        /**
         * Retrieves the root project directory.
         */
        std::string getDirectory() const;

    protected:
        /**
         * Clears a category of resources from memory.
         */
        template <typename T>
        void clear(std::map<std::string, T*>& resources)
        {
            for (auto item : resources) {
                delete item.second;
            }
            resources.clear();
        }

    public:
        /**
         * Clears this entire project from memory.
         */
        void clear();

        /**
         * Generates a complete JSON representation of the project.
         */
        Json toJson() const;
    };
}

#endif
