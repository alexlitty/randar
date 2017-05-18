#ifndef RANDAR_RENDER_GEOMETRY_HPP
#define RANDAR_RENDER_GEOMETRY_HPP

#include <randar/Render/VertexBuffer.hpp>

namespace randar
{
    class Geometry : virtual public GraphicsContextResource
    {
    protected:
        VertexBuffer vertices;
        IndexBuffer indices;

    public:
        /**
         * Disable assignment.
         */
        Geometry(const Geometry& other) = delete;
        Geometry& operator =(const Geometry& other) = delete;

        /**
         * Constructor.
         */
        Geometry(GraphicsContext& context);

        /**
         * Destructor.
         */
        ~Geometry();

        void initialize();
        void uninitialize();
        bool isInitialized();

        void appendVertex(const Vertex& vertex);
        void appendIndex(unsigned int index);
    };
}

#endif
