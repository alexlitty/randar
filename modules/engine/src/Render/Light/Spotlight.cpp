#include <randar/Render/Light/Spotlight.hpp>

// Constructor.
randar::Spotlight::Spotlight(randar::GraphicsContext& context)
: randar::BaseLight(context)
{
    this->framebuffer.camera().ortho(-10, 10, -10, 10);
    this->framebuffer.camera().range(-10, 20);
    this->framebuffer.camera().position(Vector3(0, 0, 5));
    this->framebuffer.camera().target(Vector3(0, 0, 0));
}

// Generates the lightmap of a world.
void randar::Spotlight::generateMap(randar::World& world)
{
    this->framebuffer.draw(world, false);
}
