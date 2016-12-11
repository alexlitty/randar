#ifndef RANDAR_RENDER_MATERIAL_HPP
#define RANDAR_RENDER_MATERIAL_HPP

#include <randar/render/Color.hpp>

namespace randar
{
    struct Material
    {
        Color ambientColor;
        Color diffuseColor;
    };
}

#endif
