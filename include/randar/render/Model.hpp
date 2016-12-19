#ifndef RANDAR_RENDER_MODEL_HPP
#define RANDAR_RENDER_MODEL_HPP

#include <randar/render/Drawable.hpp>
#include <randar/render/Joint.hpp>
#include <randar/render/Material.hpp>
#include <randar/render/Mesh.hpp>
#include <randar/render/ShaderProgram.hpp>

namespace randar
{
    struct Model : virtual public Drawable
    {
        ShaderProgram *shaderProgram = nullptr;
        std::vector<Joint*> joints;
        Mesh mesh;

        ~Model();

        void draw() const;
    };
}

#endif
