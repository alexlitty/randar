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

// Destructor.
randar::Model::~Model()
{
    this->gpu.destroy(this->vertexBuffer);
    this->gpu.destroy(this->faceBuffer);

    for (auto joint : this->joints) {
        delete joint;
    }
}
