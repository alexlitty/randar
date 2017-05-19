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

// Binds the associated context for further operations.
void randar::GraphicsContextResource::bindContext()
{
    if (!this->ctx) {
        throw std::runtime_error("Graphics context unavailable");
    }

    this->ctx->use();
}
