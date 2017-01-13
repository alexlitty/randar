#include <randar/Engine/Project.hpp>

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

// Loads a project into memory.
bool randar::Project::load(const std::string& directory)
{
    this->clear();
    
    this->directory = directory;
    Json project = Json::parse(
        randar::readAsciiFile(directory + "project.json")
    );

    this->name = project["name"];

    return true;
}

// Saves this project to disk.
bool randar::Project::save() const
{
    if (this->directory == "") {
        return false;
    }
    return true;
}

// Clears this entire project from memory.
void randar::Project::clear()
{
    this->clear(this->shaderPrograms);
    this->clear(this->textures);

    this->directory = "";
    this->name = "";
}

// Generates a complete JSON representation of the project.
Json randar::Project::toJson() const
{
    Json result;
    result["name"] = this->name;
    result["textures"] = randar::toJson(this->textures);
    return result;
}
