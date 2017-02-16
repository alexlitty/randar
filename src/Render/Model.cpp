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

// Sets and retrieves the number of required mesh textures.
void randar::Model::setMeshTextureCount(uint16_t newMeshTextureCount)
{
    this->meshTextureCount = newMeshTextureCount;
}

uint16_t randar::Model::getMeshTextureCount() const
{
    return this->meshTextureCount;
}

// Checks whether this model is missing mesh textures.
bool randar::Model::isMissingMeshTextures() const
{
    return this->getMeshTextureCount() != this->meshTextures.size();
}

// Checks whether this model requires any mesh textures.
bool randar::Model::requiresMeshTextures() const
{
    return this->getMeshTextureCount() > 0;
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
