#ifndef RANDAR_RENDER_MESH_HPP
#define RANDAR_RENDER_MESH_HPP

#include <randar/System/GraphicsContextResource.hpp>
#include <randar/Render/Vertex.hpp>

namespace randar
{
    /**
     * A piece of geometry composed with vertices.
     *
     * All meshes have an indexed list of unique vertices that may appear in the
     * geometry, and another ordered list of vertex indices that defines shape.
     *
     * Two vertices that have identical attributes will only appear once in the
     * indexed list. Two vertices that differ even slightly are not considered
     * identical and will both appear in the list.
     *
     * The list of vertex indices may (and almost always will) repeat vertices.
     *
     * Although the vertices of a mesh define joints and texture placement, they
     * are mapped to poses and actual textures in the Model class. We separate
     * this behavior so one mesh may efficiently be used in multiple models.
     */
    class Mesh : virtual public GraphicsContextResource
    {
    protected:
        /**
         * OpenGL name for the vertex array.
         */
        GLuint vertexArrayName;

        /**
         * Count of the number of vertex attribute buffers created.
         */
        uint8_t attributeBufferCount;

        /**
         * OpenGL names for the vertex attribute arrays.
         */
        GLuint positionBufferName;
        GLuint colorBufferName;

        /**
         * OpenGL name for the index buffer array.
         */
        GLuint indexBufferName;

        /**
         * Indexed list of unique vertices that may appear in the mesh.
         */
        std::vector<Vertex> vertices;

        /**
         * List of vertices, by index, that define the shape of the mesh.
         */
        std::vector<uint32_t> indices;

        /**
         * Whether the OpenGL buffers need to be updated with the vertices and
         * indices in memory.
         *
         * This value of this member carries no meaning when the mesh is not
         * initialized.
         */
        bool isSynced;

    public:
        /**
         * Disable assignment.
         */
        Mesh(const Mesh& other) = delete;
        Mesh& operator =(const Mesh& other) = delete;

        /**
         * Constructor.
         *
         * Initializes an empty mesh with no geometry.
         */
        Mesh(GraphicsContext& context);

        /**
         * Destructor.
         */
        ~Mesh();

    protected:
        /**
         * Helper functions to create OpenGL buffers.
         *
         * An exception is thrown if a buffer could not be created.
         */
        void createBuffer(const std::string& name, GLuint& glName);

        void createAttributeBuffer(
            const std::string& name,
            GLuint& glName,
            GLenum valueType,
            GLboolean valueNormalized,
            GLint valueCount);

        /**
         * Initializes the mesh on the associated graphics context.
         *
         * This does not push the vertices and indices in memory to the OpenGL
         * buffers.
         *
         * Nothing happens if the mesh is already initialized.
         */
        void initialize();

        /**
         * Uninitializes the mesh from the associated graphics context.
         *
         * If the mesh is only partially initialized -- for example, if the
         * vertex array is initialized but none of the buffers are -- the
         * initialized components are uninitialized.
         *
         * Nothing happens if the mesh is not initialized.
         */
        void uninitialize();

        /**
         * Whether this mesh is initialized on the associated graphics context.
         */
        bool isInitialized() const;

    };
}

#endif
