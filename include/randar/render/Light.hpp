#ifndef RANDAR_RENDER_LIGHT_HPP
#define RANDAR_RENDER_LIGHT_HPP

#include <randar/render/RenderTexture.hpp>

namespace randar
{
    class Light
    {
        randar::Shader shadowVertexShader;
        randar::Shader shadowFragmentShader;
        randar::ShaderProgram shadowProgram;

    public:
        RenderTexture renderTexture;

        Light();
        void bind() const;
    };
}

#endif
