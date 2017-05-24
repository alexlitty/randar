#ifndef RANDAR_RENDER_MODEL_HPP
#define RANDAR_RENDER_MODEL_HPP

#include <randar/Math/Transform.hpp>
#include <randar/Render/Geometry.hpp>

namespace randar
{
    class Model : virtual public Transform
    {
    protected:
        Geometry* geo = nullptr;
        ShaderProgram* program = nullptr;

    public:
        /**
         * Disable assignment.
         */
        Model(const Model& other) = delete;
        Model& operator =(const Model& other) = delete;

        /**
         * Constructors.
         */
        Model();

        /**
         * Destructor.
         */
        ~Model();

        /**
         * Sets and retrieves the model geometry.
         */
        void geometry(Geometry& newGeometry);
        Geometry& geometry();
        bool hasGeometry() const;

        /**
         * Sets and retrieves the shader program used by the model.
         */
        void shaderProgram(ShaderProgram& newProgram);
        ShaderProgram& shaderProgram();
        bool hasShaderProgram() const;

        /**
         * Draws the geometry to a framebuffer.
         */
        void drawTo(Framebuffer& fb);
    };
}

#endif
