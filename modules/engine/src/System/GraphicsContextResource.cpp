#include <randar/System/GraphicsContextResource.hpp>

// Default constructor.
randar::GraphicsContextResource::GraphicsContextResource(
    GraphicsContext* initCtx
)
: ctx(initCtx)
{
    if (this->ctx) {
        this->ctx->associate(*this);
    }
}

// Destructor.
randar::GraphicsContextResource::~GraphicsContextResource()
{
    if (this->ctx) {
        this->ctx->unassociate(*this);
    }
}
