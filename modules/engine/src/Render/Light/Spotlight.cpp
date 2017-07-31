#include <randar/Render/Light/Spotlight.hpp>

// Constructor.
randar::Spotlight::Spotlight(randar::GraphicsContext& context)
: randar::BaseLight(context)
{

}

// Generates the lightmap of a world.
void randar::Spotlight::generateMap(randar::World& world)
{
    this->framebuffer.draw(world, false);
}
