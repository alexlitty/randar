#include <randar/Scene/Object.hpp>

// Constructor.
randar::Object::Object(uint32_t initId, randar::Model* initModel)
: id(initId),
  model(initModel)
{

}

// Destructor.
randar::Object::~Object()
{
    for (auto action : this->actions) {
        delete action;
    }
}

// Builds the states in a frame range.
void randar::Object::build(const randar::FrameRange& frames)
{
    uint32_t frameId = frames.getStart();
    ModelState state;

    if (frames.getEnd().isFinal()) {
        throw std::runtime_error(
            "Must specify absolute final frame when building scene model"
        );
    }

    // Resize states array if necessary.
    if (frames.getEnd().get() >= this->states.size()) {
        this->states.resize(
            this->states.size() + (frames.getEnd().get() - this->states.size() + 1)
        );
    }

    // Rewind to the first frame before this range.
    if (frameId != 0) {
        state = this->states[frameId - 1];
    }
    state.apply(*this->model);

    while (frameId <= frames.getEnd()) {
        for (auto action : this->actions) {
            if (action->frames.contains(frameId)) {
                action->apply();
            }
        }

        state.set(*this->model);
        this->states[frameId] = state;
        frameId++;
    }
}

// Returns the model this object represents.
randar::Model& randar::Object::get()
{
    return *this->model;
}

randar::Object::operator randar::Model&()
{
    return this->get();
}

// Returns a JSON representation of this scene model.
Json randar::Object::toJson() const
{
    Json result = {
        { "actions", randar::toJson(this->actions) }
    };
    
    if (this->model) {
        result["modelId"] = this->model->id.get();
    } else {
        result["modelId"] = nullptr;
    }

    return result;
}
