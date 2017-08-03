#include <randar/Render/Light/BaseLight.hpp>

// Constructor.
randar::BaseLight::BaseLight(randar::GraphicsContext& context)
: randar::GraphicsContextResource(&context),
  framebuffer(context),
  lightmap(context, 1024, 1024, "depth")
{
    this->framebuffer.attach(this->lightmap);
}

// Returns the latest lightmap.
randar::Texture& randar::BaseLight::map()
{
    return this->lightmap;
}

// Returns the MVP matrix being used by the light.
glm::mat4 randar::BaseLight::matrix()
{
    // Used to convert to texture coordinates.
	static glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);

    return biasMatrix * (this->framebuffer.camera().projectionMatrix()
         * this->framebuffer.camera().viewMatrix());
}
