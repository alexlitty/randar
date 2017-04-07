#include <randar/Log/DefaultLog.hpp>
#include <randar/Project/Project.hpp>

// Default constructor.
randar::Project::Project()
{

}

// Copy constructor.
randar::Project::Project(const randar::Project& other)
{
    this->load(other.directory);
}

// Destructor.
randar::Project::~Project()
{
    this->clear();
}

// Retrieves the filename of the primary project file.
randar::File randar::Project::getProjectFile() const
{
    return this->directory.getFile("project", "json");
}

// Loads a project into memory.
void randar::Project::load(const randar::Directory& newDirectory)
{
    this->clear();
    this->directory = newDirectory;

    // Load resources.
    this->resources.load(this->directory.getSubdirectory("resources"));

    // Parse the main project file.
    Json project;
    try {
        project = Json::parse(
            randar::readAsciiFile(this->getProjectFile().toString())
        );
    }

    catch (const std::invalid_argument& ex) {
        throw std::runtime_error(
            std::string("Corrupt project file: ") + ex.what()
        );
    }

    if (project["name"].is_string()) {
        this->name = project["name"];
    }
}

// Saves this project to disk.
void randar::Project::save()
{
    randar::writeAsciiFile(
        this->getProjectFile().toString(),
        Json({
            { "name", this->name }
        }).dump()
    );

    this->resources.save();
}

// Retrieves the root project directory.
std::string randar::Project::getDirectory() const
{
    return this->directory;
}

// Clears this entire project from memory.
void randar::Project::clear()
{
    this->resources.clear();

    this->directory = ".";
    this->name = "Untitled Project";
}

// Generates a complete JSON representation of the project.
Json randar::Project::toJson() const
{
    Json result = this->resources.toJson();
    result["name"] = this->name;

    return result;
}
