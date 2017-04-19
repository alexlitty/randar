#include <randar/System/GraphicsContext.hpp>

// Constructor.
randar::GraphicsContext::GraphicsContext()
{

}

// Signals the requirement for a process-wide graphics context.
void randar::GraphicsContext::require()
{
    if (!this->ctx) {
        this->ctx = new randar::GraphicsContext;
    }
}

// Destroys the process-wide graphics context.
void randar::GraphicsContext::destroy()
{
    if (this->ctx) {

    }
}

// Process-wide graphics context.
randar::GraphicsContext* ctx = nullptr;
