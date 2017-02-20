#include <randar/Scene/SceneModel.hpp>

// Constructor.
randar::SceneModel::SceneModel(uint32_t initId, randar::Model* initModel)
: id(initId),
  model(initModel)
{

}

// Destructor.
randar::SceneModel::~SceneModel()
{
    for (auto action : this->actions) {
        delete action;
    }
}

// Returns the model this object represents.
randar::Model& randar::SceneModel::get()
{
    return *this->model;
}

randar::SceneModel::operator randar::Model&()
{
    return this->get();
}
