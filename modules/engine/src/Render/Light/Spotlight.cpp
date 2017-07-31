#include <randar/Render/Light/Spotlight.hpp>

// Constructor.
randar::Spotlight::Spotlight(randar::GraphicsContext& context)
: randar::BaseLight(context)
{

}

// Generates and returns the light's map.
randar::Texture& randar::Spotlight::lightmap(randar::World& world)
{
    this->framebuffer.draw(world);
    return this->map;
}
