#include <randar/shape/Cuboid.hpp>

#include <iostream>
randar::Cuboid::Cuboid(const randar::Vector& min, const randar::Vector& max)
{
    this->appendVertex(min);
    this->appendVertex(Vector(min.x, min.y, max.z));
    this->appendVertex(Vector(min.x, max.y, min.z));
    this->appendVertex(Vector(min.x, max.y, max.z));

    this->appendVertex(Vector(max.x, min.y, min.z));
    this->appendVertex(Vector(max.x, min.y, max.z));
    this->appendVertex(Vector(max.x, max.y, min.z));
    this->appendVertex(max);

    this->appendFace(0, 1, 2);
    this->appendFace(3, 1, 2);

    this->vertices.send();
    this->send();
}
