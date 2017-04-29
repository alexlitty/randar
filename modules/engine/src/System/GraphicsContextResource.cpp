#include <randar/System/GraphicsContextResource.hpp>

// Default constructor.
randar::GraphicsContextResource::GraphicsContextResource()
: ctx(nullptr)
{

}

// Destructor.
randar::GraphicsContextResource::~GraphicsContextResource()
{
    if (this->ctx) {
        this->unassociate();
    }
}

// Associates the resource with a context.
void randar::GraphicsContextResource::associate(randar::GraphicsContext& newCtx)
{
    if (this->ctx) {
        throw std::runtime_error("Resource is already associated with a context");
    }

    this->ctx = &newCtx;
    this->ctx->resources.insert(this);
    this->initialize();
}

// Unassociates the resource from the currently associated context.
void randar::GraphicsContextResource::unassociate()
{
    if (!this->ctx) {
        throw std::runtime_error("Resource has no context to unassociate from");
    }

    if (this->isInitialized()) {
        this->uninitialize();
    }

    unsigned int countErased = this->ctx->resources.erase(this);
    this->ctx = nullptr;

    if (!countErased) {
        throw std::runtime_error("Context resource list corruption");
    }
}
