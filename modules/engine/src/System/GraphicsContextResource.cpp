#include <randar/System/GraphicsContextResource.hpp>

// Default constructor.
randar::GraphicsContextResource::GraphicsContextResource(
    GraphicsContext* initCtx
)
: ctx(nullptr)
{
    if (initCtx) {
        initCtx->associate(*this);
    }
}

// Destructor.
randar::GraphicsContextResource::~GraphicsContextResource()
{
    if (this->ctx) {
        this->ctx->unassociate(*this);
    }
}
