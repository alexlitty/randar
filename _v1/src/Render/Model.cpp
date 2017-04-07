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

// Sets a mesh texture.
void randar::Model::setMeshTexture(uint32_t slotId, randar::Texture* texture)
{
    if (slotId >= this->meshTextures.size()) {
        throw std::logic_error("Assigning to invalid texture slot on model");
    }

    if (this->meshTextures[slotId] == texture) {
        return;
    }

    this->meshTextures[slotId] = texture;
    this->dirty = true;
}

// Whether this model has changed since last being saved.
bool randar::Model::isDirty() const
{
    return this->dirty;
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
