#ifndef RANDAR_RENDER_VIEWPORT_HPP
#define RANDAR_RENDER_VIEWPORT_HPP

namespace randar
{
    struct Viewport
    {
        int x1;
        int y1;

        int x2;
        int y2;

        Viewport(int ix1, int iy1, int ix2, int iy2);
        void set(int ix1, int iy1, int ix2, int iy2);
    };
}

#endif
