#ifndef RANDAR_RENDER_MODEL_HPP
#define RANDAR_RENDER_MODEL_HPP

#include <randar/Physics/Physical.hpp>
#include <randar/Render/Joint.hpp>
#include <randar/Render/Material.hpp>
#include <randar/Render/Mesh.hpp>
#include <randar/Render/ShaderProgram.hpp>

namespace randar
{
    struct Model : virtual public Physical
    {
    protected:
        ShaderProgram shaderProgram;

    public:
        Shader vertexShader;
        Shader fragmentShader;
        Mesh mesh;

        std::vector<Joint*> joints;

        ~Model();

        const ShaderProgram& getShaderProgram() const;
    };
}

#endif
