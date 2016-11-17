#ifndef RANDAR_RENDER_RENDER_STATE_HPP
#define RANDAR_RENDER_RENDER_STATE_HPP

#include <randar/render/ShaderProgram.hpp>

namespace randar
{
    struct RenderState
    {
        ShaderProgram *shaderProgram = nullptr;
    };
}

#endif
