#include <randar/render/Viewport.hpp>

randar::Viewport::Viewport(int ix1, int iy1, int ix2, int iy2)
{
    this->set(ix1, iy1, ix2, iy2);
}

void randar::Viewport::Viewport(int ix1, int iy1, int ix2, int iy2)
{
    this->x1 = ix1;
    this->y1 = iy1;

    this->x2 = ix2;
    this->y2 = iy2;
}
