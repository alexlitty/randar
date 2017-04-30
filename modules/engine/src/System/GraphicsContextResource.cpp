#include <randar/System/GraphicsContextResource.hpp>

// Default constructor.
randar::GraphicsContextResource::GraphicsContextResource(
    GraphicsContext* initCtx
)
: ctx(initCtx)
{

}

// Destructor.
randar::GraphicsContextResource::~GraphicsContextResource()
{
    if (this->ctx && this->ctx->isAssociated(*this)) {
        this->ctx->unassociate(*this);
    }
}
