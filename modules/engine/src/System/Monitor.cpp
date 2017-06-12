#include <randar/System/Monitor.hpp>

// Constructor.
randar::Monitor::Monitor(randar::GraphicsContext& context, randar::Geometry& geometry)
: randar::GraphicsContextResource(&context),
  geo(&geometry)
{
    this->win = &this->ctx->window(800, 600);
    this->win->camera().projection();
    this->win->camera().move(Vector3(0, 0, -10));
    this->win->camera().target(Vector3(0, 0, 0));
}

// Assignment.
randar::Monitor::Monitor(randar::Monitor&& other)
: randar::GraphicsContextResource(&other.context())
{
    this->win = other.win;
    other.win = nullptr;

    this->geo = other.geo;
    other.geo = nullptr;
}

// Destructor.
randar::Monitor::~Monitor()
{
    delete this->win;
}

// Presents the monitor to the screen.
void randar::Monitor::present()
{
    this->win->clear();

    if (this->geo) {
        this->win->draw(*this->geo);
    }

    this->win->present();
}
