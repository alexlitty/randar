#ifndef RANDAR_RENDER_MODEL_HPP
#define RANDAR_RENDER_MODEL_HPP

#include <randar/Math/Transform.hpp>
#include <randar/Render/Geometry.hpp>
#include <randar/Render/Skeleton.hpp>

namespace randar
{
    class Model : public Transform
    {
    protected:
        Geometry* geo;
        ShaderProgram* program;
        Skeleton* skel;

    public:
        /**
         * Constructors.
         */
        Model();

        /**
         * Assignment.
         */
        Model(const Model& other);
        Model& operator =(const Model& other);

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
         * Sets and retrieves the skeleton applied to the model.
         */
        void skeleton(Skeleton& skeleton);
        Skeleton& skeleton();
        bool hasSkeleton() const;
    };

    /**
     * Node.js helper for intuitive model creation.
     */
    Model model();
}

#endif
