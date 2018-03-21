#include <randar/Render/Light/Spotlight.hpp>

// Constructors.
randar::Spotlight::Spotlight()
: randar::Spotlight(randar::context())
{

}

randar::Spotlight::Spotlight(randar::GraphicsContext& context)
: randar::BaseLight(context)
{
    this->framebuffer.camera().ortho(-1000, 1000, -1000, 1000);
    this->framebuffer.camera().viewport.x1 = 0;
    this->framebuffer.camera().viewport.x2 = 1024;
    this->framebuffer.camera().viewport.y1 = 0;
    this->framebuffer.camera().viewport.y2 = 1024;

    this->range(-10, 20);
    this->position(Vector3(0, 0, 5));
    this->target(Vector3(0, 0, 0));
}

// Sets and retrieves position.
void randar::Spotlight::position(const Vector3& newPosition)
{
    this->framebuffer.camera().position(newPosition);
}

void randar::Spotlight::move(const Vector3& movement)
{
    this->framebuffer.camera().move(movement);
}

randar::Vector3 randar::Spotlight::position()
{
    return this->framebuffer.camera().position();
}

// Sets and retrieves the target vector.
void randar::Spotlight::target(const randar::Vector3& newTarget)
{
    this->framebuffer.camera().target(newTarget);
}

randar::Vector3 randar::Spotlight::target()
{
    return this->framebuffer.camera().target();
}

// Sets light range.
void randar::Spotlight::range(float near, float far)
{
    this->framebuffer.camera().range(near, far);
}

// Generates the lightmap of a world.
void randar::Spotlight::generateMap(randar::World& world)
{
    this->framebuffer.draw(world, false);
}
