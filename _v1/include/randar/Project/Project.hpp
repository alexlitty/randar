#ifndef RANDAR_ENGINE_PROJECT_HPP
#define RANDAR_ENGINE_PROJECT_HPP

#include <randar/Project/ResourceRepository.hpp>
#include <randar/Render/ShaderProgram.hpp>
#include <randar/Render/Model.hpp>
#include <randar/Utility/File.hpp>
#include <randar/Utility/Json.hpp>
#include <randar/Utility/Map.hpp>

namespace randar
{
    class Project
    {
        Directory directory;

    public:
        std::string name;
        ResourceRepository resources;

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
        File getProjectFile() const;

    public:
        /**
         * Loads a project into memory, given a project directory.
         *
         * Throws a runtime error if the project could not be loaded at all.
         */
        void load(const Directory& newDirectory);

        /**
         * Saves this project to disk.
         */
        void save();

        /**
         * Retrieves the root project directory.
         */
        std::string getDirectory() const;

        /**
         * Frees this project from memory.
         */
        void clear();

        /**
         * Generates a complete JSON representation of the project.
         */
        Json toJson() const;
    };
}

#endif
