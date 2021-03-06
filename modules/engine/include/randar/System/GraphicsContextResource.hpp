#ifndef RANDAR_SYSTEM_GRAPHICS_CONTEXT_RESOURCE_HPP
#define RANDAR_SYSTEM_GRAPHICS_CONTEXT_RESOURCE_HPP

#include <stdexcept>
#include <randar/System/GraphicsContext.hpp>

namespace randar
{
    /**
     * Resource which can be initialized on a graphics context.
     *
     * All resources represent one or more lower-level OpenGL concepts. Most
     * resources have a one-to-one association with a GL identifier, but this is
     * not always the case. Indeed, a child of this class could just be an
     * aggregation of multiple "real" OpenGL concepts and not have an identifier
     * itself.
     *
     * A resource may not always be initialized at all times -- In fact, in some
     * cases, a resource may exist without ever being initialized.
     *
     * A framebuffer is a core resource that must be immediately initialized
     * onto a context, and never needs to be uninitialized for its lifetime. On
     * the other hand, a shader can be a conceptual resource that doesn't need
     * to be initialized at all times.
     *
     * To elaborate, consider a UI user updating a shader's definition. While it
     * is being modified, the shader has no purpose in being initialized, but
     * the "concept" of this specific shader still exists as an object in
     * memory. It may then be initialized and uninitialized as required, when it
     * is previewed or used in a scene.
     *
     * Any resource, regardless of its type, is considered uninitialized if its
     * associated context is destroyed before the resource itself.
     *
     * This is a supported and valid use-case. The Node.js adapter allows us to
     * directly create resources and contexts in separately tracked v8 values,
     * which will be picked up by garbage collection in unpredictable order.
     */
    class GraphicsContextResource : virtual public Resource
    {
        friend GraphicsContext;

    protected:
        /**
         * Graphics context on which the resource is initialized, or will be
         * initialized upon when desired.
         *
         * May be nullptr, in which case the resource is not initialized on any
         * graphics context.
         *
         * Do not let children set this value directly, otherwise contexts won't
         * be aware of the resource's existence and destructions will become
         * prone to segfaults. Use the context's associate & unassociate methods
         * instead.
         */
        GraphicsContext* ctx;

    public:
        /**
         * Explicitly disable assignment.
         *
         * Children may provide their own assignment behavior.
         */
        GraphicsContextResource(const GraphicsContextResource& other) = delete;

        GraphicsContextResource& operator =(
            const GraphicsContextResource& other
        ) = delete;

        /**
         * Constructor.
         */
        GraphicsContextResource(GraphicsContext* initCtx);

        /**
         * Destructor.
         *
         * If the resource is initialized, it is uninitialized. Otherwise
         * nothing special happens.
         */
        virtual ~GraphicsContextResource();

        /**
         * Associates the resource with a context.
         *
         * If an association already exists with a different context, it is
         * unassociated with the old context first.
         *
         * If the context is already associated with the resource, nothing
         * happens.
         */
        void context(GraphicsContext& context);

        /**
         * Gets the context associated with this resource.
         *
         * Throws an exception if no context is associated.
         */
        GraphicsContext& context();

        /**
         * Unassociates the resource from its associated context.
         *
         * If the resource is not associated with a context, nothing happens. If
         * the resource is, it is uninitialized before unassociation.
         */
        void unassociateContext();

        /**
         * Binds the associated context for further operations.
         *
         * Throws an exception if the context is not available.
         */
        void bindContext();

        /**
         * Whether this resource has an assigned context.
         */
        bool hasContext() const;

        /**
         * Checks if this resource has an assigned context.
         *
         * Throws an exception if no context is assigned.
         */
        void ensureContext() const;

        /**
         * Whether this resource and another resource use the same context.
         */
        bool sameContext(GraphicsContextResource& resource) const;

        /**
         * Initializes the resource, if applicable.
         *
         * By default nothing happens.
         */
        virtual void initialize();
        virtual void initialize(GraphicsContext& context);

        /**
         * Uninitializes the resource, if applicable.
         *
         * By default nothing happens.
         */
        virtual void uninitialize();

        /**
         * Human-friendly description of the resource.
         *
         * Should be overriden by children.
         */
        virtual std::string description() override;
    };
}

#endif
