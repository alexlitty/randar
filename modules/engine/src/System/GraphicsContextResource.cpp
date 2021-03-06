#include <randar/System/GraphicsContextResource.hpp>

// Default constructor.
randar::GraphicsContextResource::GraphicsContextResource(
    GraphicsContext* initCtx
)
: ctx(nullptr)
{
    if (initCtx) {
        this->context(*initCtx);
    }
}

// Destructor.
randar::GraphicsContextResource::~GraphicsContextResource()
{
    this->unassociateContext();
}

// Associates the resource with a context.
void randar::GraphicsContextResource::context(randar::GraphicsContext& context)
{
    if (this->ctx) {
        this->unassociateContext();
    }

    this->ctx = &context;
    this->ctx->associate(*this);
}

// Gets the context associated with this resource.
randar::GraphicsContext& randar::GraphicsContextResource::context()
{
    if (!this->ctx) {
        throw std::runtime_error("No graphics context assigned");
    }

    return *this->ctx;
}

// Unassociates the resource from its associated context.
void randar::GraphicsContextResource::unassociateContext()
{
    if (this->ctx) {
        this->uninitialize();
        this->ctx = nullptr;
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

// Whether this resource has an assigned context.
bool randar::GraphicsContextResource::hasContext() const
{
    return this->ctx != nullptr;
}

// Checks if this resource has an assigned context.
void randar::GraphicsContextResource::ensureContext() const
{
    if (!this->hasContext()) {
        throw std::runtime_error("No context assigned");
    }
}

// Whether this resource and another resource use the same context.
bool randar::GraphicsContextResource::sameContext(
    randar::GraphicsContextResource& resource) const
{
    return resource.hasContext() && this->ctx == &resource.context();
}

// Initializes the resource, if applicable.
void randar::GraphicsContextResource::initialize()
{

}

void randar::GraphicsContextResource::initialize(randar::GraphicsContext& context)
{
    this->unassociateContext();
    this->context(context);
    this->initialize();
}

// Uninitializes the resource, if applicable.
void randar::GraphicsContextResource::uninitialize()
{

}

// Human-friendly description of the resource.
std::string randar::GraphicsContextResource::description()
{
    return "[GraphicsContextResource | Unknown subresource]";
}
