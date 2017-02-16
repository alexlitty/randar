#include <randar/Project/ResourceRepository.hpp>
#include <randar/Filesystem/BinaryFileReader.hpp>

void randar::ResourceRepository::importRaModel(const File& file)
{
    std::string basename = file.getBaseName();
    if (!randar::isInteger(basename)) {
        return;
    }

    uint8_t version;
    uint32_t vertexCount;
    uint32_t faceCount;
    uint16_t textureCount;
    uint32_t jointCount;
    uint16_t jointWeightCount;

    BinaryFileReader stream(file);

    // Check model file version.
    stream.read(version);
    if (version != 0) {
        return;
    }

    // Read basic model information.
    stream.read(vertexCount);
    stream.read(faceCount);
    stream.read(textureCount);
    stream.read(jointCount);
    stream.read(jointWeightCount);

    // Create model.
    Model *model = new Model;
    model->id.set(std::stoi(basename));

    // Read vertices.
    for (unsigned int i = 0; i < vertexCount; i++) {
        Vertex vertex;
        stream.read(vertex.position.x);
        stream.read(vertex.position.y);
        stream.read(vertex.position.z);
        
        stream.read(vertex.color.r);
        stream.read(vertex.color.g);
        stream.read(vertex.color.b);

        stream.read(vertex.textureId);
        stream.read(vertex.textureCoordinate.u);
        stream.read(vertex.textureCoordinate.v);

        for (unsigned int j = 0; j < jointWeightCount; j++) {
            unsigned char jointIndex, jointWeight;
            stream.read(jointIndex);
            stream.read(jointWeight);
            vertex.jointWeights[jointIndex] = jointWeight;
        }

        model->vertices.push_back(vertex);
    }

    // Read faces.
    for (unsigned int i = 0; i < faceCount; i++) {
        for (unsigned int j = 0; j < 3; j++) {
            unsigned int faceIndex;
            stream.read(faceIndex);
            model->faceIndices.push_back(faceIndex);
        }
    }

    // Read joints.
    for (unsigned int i = 0; i < jointCount; i++) {
        Joint *joint = new Joint;
        stream.read(joint->name);
        stream.read(joint->parentId);
        model->joints.push_back(joint);
    }

    // Assign parent joint pointers.
    for (auto joint : model->joints) {
        if (joint->parentId >= 0) {
            if (joint->parentId >= static_cast<int32_t>(model->joints.size())) {
                std::cout << "Treating joint as root: Parent does not exist" << std::endl;
                joint->parentId = -1;
                continue;
            }

            joint->parent = model->joints[joint->parentId];
        }
    }

    // Read textures.
    bool isTextureProvided;
    uint32_t textureId;

    for (unsigned int i = 0; i < textureCount; i++) {
        stream.read(isTextureProvided);

        if (isTextureProvided) {
            stream.read(textureId);

            if (!this->textures.count(textureId)) {
                throw std::runtime_error("Importing model with orphaned texture");
            }

            model->meshTextures.push_back(this->textures[textureId]);
        }

        else {
            model->meshTextures.push_back(nullptr);
        }

    }

    this->gpu.write(*model);
    this->models[model->id.get()] = model;
}
