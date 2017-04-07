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

        Viewport(int ix1 = 0, int iy1 = 0, int ix2 = 1, int iy2 = 1);
        void set(int ix1, int iy1, int ix2, int iy2);
    };
}

#endif
