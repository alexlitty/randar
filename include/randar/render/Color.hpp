#ifndef RANDAR_RENDER_COLOR_HPP
#define RANDAR_RENDER_COLOR_HPP

namespace randar
{
    struct Color
    {
        float r;
        float g;
        float b;
        float a;

        Color();
        Color(float rInit, float gInit, float bInit, float aInit = 1.0f);
    };
}

#endif
