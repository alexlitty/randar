#include <randar/Scene/Scene.hpp>
#include <randar/Utility/Map.hpp>

// Destructor.
randar::Scene::~Scene()
{
    for (auto item : this->objects) {
        delete item.second;
    }
}

// Retrieves scene data as JSON.
Json randar::Scene::toJson() const
{
    return {
        { "name", "Untitled Scene" },
        { "fps",  this->fps        },

        { "objects", randar::toJson(this->objects) }
    };
}
