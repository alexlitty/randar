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
std::string randar::Project::getProjectFilename() const
{
    return this->directory.toString() + "project.json";
}

// Loads a project into memory.
void randar::Project::load(const std::string& directory)
{
    this->clear();
    
    this->directory = directory;

    // Load resources.
    this->resources.load(this->directory.getSubdirectory("resources"));

    // Parse the main project file.
    Json project;
    try {
        project = Json::parse(
            randar::readAsciiFile(this->getProjectFilename())
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

    if (project["shaders"].is_object()) {
        for (auto shaderProgram : project["shaders"]) {

        }
    }

    if (project["textures"].is_object()) {
        for (Json::iterator it = project["textures"].begin(); it != project["textures"].end(); it++) {
            this->textures[it.key()] = new Texture(
                it.value().get<std::string>()
            );
        }
    }

    if (project["models"].is_object()) {
        for (Json::iterator it = project["models"].begin(); it != project["models"].end(); it++) {
            Model *model;

            try {
                model = new Model(
                    it.value().get<std::string>(),
                    this->textures
                );

                this->models[it.key()] = model;
            }

            catch (std::runtime_error error) {
                randar::logError("Removing bad model from project: " + it.key());
            }
        }
    }
}

// Saves this project to disk.
bool randar::Project::save() const
{
    if (this->directory.toString() == "") {
        return false;
    }

    return randar::writeAsciiFile(
        this->getProjectFilename(),
        this->toJson().dump()
    );
}

// Retrieves the root project directory.
std::string randar::Project::getDirectory() const
{
    return this->directory;
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

    for (auto item : this->textures) {
        result["textures"][item.first] = item.second->getFile();
    }

    for (auto item : this->models) {
        result["models"][item.first] = item.second->getFile();
    }

    return result;
}
