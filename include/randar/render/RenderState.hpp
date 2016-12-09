#ifndef RANDAR_RENDER_RENDER_STATE_HPP
#define RANDAR_RENDER_RENDER_STATE_HPP

#include <randar/render/Camera.hpp>
#include <randar/render/ShaderProgram.hpp>
#include <randar/render/Transform.hpp>

namespace randar
{
    struct RenderState
    {
        ShaderProgram *shaderProgram = nullptr;
        Transform transform;
        Camera camera;
    };
}

#endif
