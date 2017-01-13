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

// Retrieves the filename of the primary project file.
std::string randar::Project::getProjectFilename() const
{
    return this->directory + "project.json";
}

// Loads a project into memory.
bool randar::Project::load(const std::string& directory)
{
    this->clear();
    
    this->directory = directory;
    Json project = Json::parse(
        randar::readAsciiFile(this->getProjectFilename())
    );

    this->name = project["name"];

    if (project["shaders"].is_object()) {
        for (auto shaderProgram : project["shaders"]) {

        }
    }

    if (project["textures"].is_object()) {
        for (Json::iterator it = project["textures"].begin(); it != project["textures"].end(); it++) {
            this->textures[it.key()] = new Texture(it.value());
        }
    }

    return true;
}

// Saves this project to disk.
bool randar::Project::save() const
{
    if (this->directory == "") {
        return false;
    }

    return randar::writeAsciiFile(
        this->getProjectFilename(),
        this->toJson().dump()
    );
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
