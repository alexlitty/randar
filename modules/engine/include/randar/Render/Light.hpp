#ifndef RANDAR_RENDER_LIGHT_HPP
#define RANDAR_RENDER_LIGHT_HPP

#include <randar/Render/ShaderProgram.hpp>
#include <randar/Utility/File.hpp>

namespace randar
{
    struct Light : virtual public Resource
    {
        Shader vertexShader;
        Shader fragmentShader;
        ShaderProgram shaderProgram;

        Light();
    };
}

#endif
