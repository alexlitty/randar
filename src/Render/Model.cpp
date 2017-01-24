#include <randar/Render/Model.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructs a new model.
randar::Model::Model()
: vertexCount(0),
  faceCount(0),
  textureCount(0),
  jointCount(0),
  jointWeightCount(0)
{

}

// Constructs an existing model from a file.
randar::Model::Model(const std::string& file)
{
    uint8_t version;

    BinaryFileInput stream(file);

    // Check model file version.
    stream.read(version);
    if (version != 0) {
        return;
    }

    // Read basic model information.
    stream.read(this->vertexCount);
    stream.read(this->faceCount);
    stream.read(this->textureCount);
    stream.read(this->jointCount);
    stream.read(this->jointWeightCount);

    // Read vertices.
    for (unsigned int i = 0; i < this->vertexCount; i++) {
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

        for (unsigned int j = 0; j < this->jointWeightCount; j++) {
            unsigned char jointIndex, jointWeight;
            stream.read(jointIndex);
            stream.read(jointWeight);
            vertex.jointWeights[jointIndex] = jointWeight;
        }

        this->vertices.push_back(vertex);
    }

    // Read faces.
    for (unsigned int i = 0; i < this->faceCount; i++) {
        for (unsigned int j = 0; j < 3; j++) {
            unsigned int faceIndex;
            stream.read(faceIndex);
            this->faceIndices.push_back(faceIndex);
        }
    }

    // Read joints.
    for (unsigned int i = 0; i < this->jointCount; i++) {
        Joint *joint = new Joint;
        stream.read(joint->name);
        stream.read(joint->parentId);
        this->joints.push_back(joint);
    }

    // Assign parent joint pointers.
    for (auto joint : this->joints) {
        if (joint->parentId >= 0) {
            if (joint->parentId >= static_cast<int32_t>(this->joints.size())) {
                std::cout << "Treating joint as root: Parent does not exist" << std::endl;
                joint->parentId = -1;
                continue;
            }

            joint->parent = this->joints[joint->parentId];
        }
    }

    this->gpu.write(*this);
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

// Saves this model to its file.
bool randar::Model::save()
{
    // Update serialization helpers.
    uint8_t version = 0;
    this->vertexCount = this->vertices.size();
    this->faceCount = this->faceIndices.size() / 3;
    this->textureCount = this->textures.size();
    this->jointCount = this->joints.size();
    this->jointWeightCount = 0;

    BinaryFileOutput stream(this->getFile());
    stream.write(version);

    // Write basic model information.
    stream.write(this->vertexCount);
    stream.write(this->faceCount);
    stream.write(this->textureCount);
    stream.write(this->jointCount);
    stream.write(this->jointWeightCount);

    // Write vertices.
    for (auto vertex : this->vertices) {
        stream.write(vertex.position.x);
        stream.write(vertex.position.y);
        stream.write(vertex.position.z);

        stream.write(vertex.color.r);
        stream.write(vertex.color.g);
        stream.write(vertex.color.b);

        stream.write(vertex.textureId);
        stream.write(vertex.textureCoordinate.u);
        stream.write(vertex.textureCoordinate.v);

        for (auto jointWeight : vertex.jointWeights) {
            stream.write(jointWeight.first);
            stream.write(jointWeight.second);
        }
    }

    // Write faces.
    for (auto faceIndex : this->faceIndices) {
        stream.write(faceIndex);
    }

    // Write joints.
    for (auto joint : this->joints) {
        stream.write(joint->name);
        stream.write(joint->parentId);
    }

    return true;
}
