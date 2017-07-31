#include <randar/Render/Light/BaseLight.hpp>

// Constructor.
randar::BaseLight::BaseLight(randar::GraphicsContext& context)
: randar::GraphicsContextResource(&context),
  framebuffer(context),
  map(context, 1024, 1024, "depth")
{
    this->framebuffer.attach(this->map);
}

// Returns the MVP matrix being used by the light.
glm::mat4 randar::BaseLight::matrix()
{
    return this->framebuffer.camera().projectionMatrix()
         * this->framebuffer.camera().viewMatrix()
         * this->transformMatrix();
}
