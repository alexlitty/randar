#include <randar/render/Canvas.hpp>

randar::Canvas::~Canvas()
{

}

void randar::Canvas::draw(const randar::Model& model, randar::RenderState state) const
{
    state.transform = model.getTransformMatrix();
    this->draw(model.mesh, state);
}
