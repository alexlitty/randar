#ifndef RANDAR_IO_RANDAR_HPP
#define RANDAR_IO_RANDAR_HPP

#include <randar/Render/Geometry.hpp>
#include <randar/System/Path.hpp>

namespace randar
{
    void importGeometry(const randar::Path& path, randar::Geometry& geo);
    void exportGeometry(const randar::Path& path, randar::Geometry& geo);
}

#endif
