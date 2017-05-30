#ifndef RANDAR_RENDER_GEOMETRY_HPP
#define RANDAR_RENDER_GEOMETRY_HPP

#include <randar/Render/Primitive.hpp>
#include <randar/Render/ShaderProgram.hpp>
#include <randar/Render/VertexBuffer.hpp>

namespace randar
{
    class Geometry : public GraphicsContextResource
    {
    public:
        VertexBuffer vertices;
        IndexBuffer indices;

        /**
         * Primitive used by the geometry.
         *
         * Describes how vertices should be interpreted.
         */
        Primitive primitive = randar::Primitive::Triangle;

        /**
         * Constructors.
         */
        Geometry();
        Geometry(GraphicsContext& context);

        /**
         * Assignment.
         */
        Geometry(const Geometry& other);
        Geometry& operator =(const Geometry& other);
        Geometry copy();

        /**
         * Destructor.
         */
        ~Geometry();

        /**
         * Identifies the Randar object type.
         */
        std::string kind() const;

        /**
         * Initializes the geometry on a context.
         */
        using GraphicsContextResource::initialize;
        virtual void initialize() override;

        /**
         * Uninitializes the geometry from a context.
         *
         * Nothing happens if the geometry is not initialized. No exceptions are
         * thrown upon failure.
         */
        virtual void uninitialize() override;

        /**
         * Whether the geometry is initialized on a context.
         */
        bool isInitialized();

        /**
         * Syncs local data to OpenGL.
         */
        void sync();

        /**
         * Clears vertices and indices of the geometry.
         *
         * Primitive remains unchanged.
         */
        void clear();

        /**
         * Adds a vertex to the geometry's available vertices.
         *
         * Returns an index that identifies the vertex in this geometry's
         * available vertices, which is later used to construct a shape.
         *
         * If the vertex already exists in the available geometry, it is not
         * appended and the existing index is returned.
         *
         * This does not manipulate the shape of the geometry.
         *
         * In most cases, you can use the simplified append method instead.
         */
        uint32_t useVertex(const Vertex& vertex);

        /**
         * Appends a vertex to the geometry shape.
         *
         * This method simply calls appendVertex, captures the index of the
         * vertex in this geometry's available vertices, and calls appendIndex
         * with it.
         *
         * This is the preferred way to append a vertex to geometry.
         */
        void append(const Vertex& vertex);

        /**
         * Saves and loads the geometry from disk.
         */
        void save(const randar::Path& filepath);
        void load(const randar::Path& filepath);
    };

    /**
     * Node.js helper.
     */
    Geometry geometry();
}

#endif
