#include <randar/Shape/Plane.hpp>

randar::Plane::Plane(const randar::Vector& min, const randar::Vector& max)
{
    this->appendVertex(Vector(-25.0f, 0, -25.0f));
    this->appendVertex(Vector(25.0f, 0, -25.0f));
    this->appendVertex(Vector(-25.0f, 0, 25.0f));
    this->appendVertex(Vector(25.0f, 0, 25.0f));

    this->appendFace(0, 1, 2);
    this->appendFace(3, 1, 2);

    this->vertices.send();
    this->send();
}
