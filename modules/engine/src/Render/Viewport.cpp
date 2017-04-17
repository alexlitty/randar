#include <randar/Render/Viewport.hpp>

randar::Viewport::Viewport()
: x1(0),
  y1(0),
  x2(1),
  y2(1)
{

}

randar::Viewport::Viewport(int ix1, int iy1, int ix2, int iy2)
{
    this->set(ix1, iy1, ix2, iy2);
}

void randar::Viewport::set(int ix1, int iy1, int ix2, int iy2)
{
    this->x1 = ix1;
    this->y1 = iy1;

    this->x2 = ix2;
    this->y2 = iy2;
}
