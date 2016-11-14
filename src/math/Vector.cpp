#include <randar/math/Vector.hpp>

randar::Vector::Vector()
: randar::Vector::Vector(0.0f, 0.0f, 0.0f)
{

}

randar::Vector::Vector(float xInit, float yInit, float zInit)
: x(xInit),
  y(yInit),
  z(zInit)
{

}
