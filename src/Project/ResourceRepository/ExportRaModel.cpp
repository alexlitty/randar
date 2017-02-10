#include <randar/Project/ResourceRepository.hpp>
#include <randar/Filesystem/BinaryFileWriter.hpp>

void randar::ResourceRepository::exportRaModel(uint32_t modelId)
{
    Model *model = this->models[modelId];
    if (!model) {
        throw std::logic_error("Exporting nonexistent model");
    }

    uint8_t version = 0;
    uint32_t vertexCount = model->vertices.size();
    uint32_t faceCount = model->faceIndices.size() / 3;
    uint32_t jointCount = model->joints.size();
    uint16_t jointWeightCount = 0;

    BinaryFileWriter stream(
        this->directory
            .getSubdirectory("models")
            .getFile(std::to_string(modelId), "raModel")
    );

    // Write basic model information.
    stream.write(version);
    stream.write(vertexCount);
    stream.write(faceCount);
    stream.write(model->getMeshTextureCount());
    stream.write(static_cast<uint16_t>(model->meshTextures.size()));
    stream.write(jointCount);
    stream.write(jointWeightCount);

    // Write vertices.
    for (auto vertex : model->vertices) {
        stream.write(vertex.position.x);
        stream.write(vertex.position.y);
        stream.write(vertex.position.z);

        stream.write(vertex.color.r);
        stream.write(vertex.color.g);
        stream.write(vertex.color.b);

        stream.write(vertex.textureId);
        stream.write(vertex.textureCoordinate.u);
        stream.write(vertex.textureCoordinate.v);

        /*for (auto jointWeight : vertex.jointWeights) {
            stream.write(jointWeight.first);
            stream.write(jointWeight.second);
        }*/
    }

    // Write faces.
    for (auto faceIndex : model->faceIndices) {
        stream.write(faceIndex);
    }
    // Write joints.
    for (auto joint : model->joints) {
        stream.write(joint->name);
        stream.write(joint->parentId);
    }

    // Write textures.
    for (auto texture : model->meshTextures) {
        stream.write(texture->id.get());
    }
}
