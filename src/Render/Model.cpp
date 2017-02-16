#include <randar/Render/Model.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructs a new model.
randar::Model::Model()
{

}

// Destructor.
randar::Model::~Model()
{
    this->gpu.destroy(this->vertexBuffer);
    this->gpu.destroy(this->faceBuffer);

    for (auto joint : this->joints) {
        delete joint;
    }
}

// Whether this model is initialized on the GPU.
bool randar::Model::isInitialized() const
{
    return this->vertexBuffer.isInitialized()
        && this->faceBuffer.isInitialized();
}

// Checks whether this model is missing mesh textures.
bool randar::Model::isMissingMeshTextures() const
{
    for (auto texture : this->meshTextures) {
        if (!texture) {
            return true;
        }
    }

    return false;
}

// Retrieves model metadata as JSON.
Json randar::Model::toJson() const
{
    Json texturesJson;
    for (auto texture : this->meshTextures) {
        if (texture) {
            texturesJson.push_back(texture->id.get());
        }

        else {
            texturesJson.push_back(nullptr);
        }
    }

    return {
        { "name", "Untitled Model" },

        { "vertexCount", this->vertices.size()        },
        { "faceCount",   this->faceIndices.size() / 3 },

        { "textures", texturesJson }
    };
}
