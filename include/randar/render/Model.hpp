#ifndef RANDAR_RENDER_MODEL_HPP
#define RANDAR_RENDER_MODEL_HPP

#include <randar/math/Transformable.hpp>
#include <randar/render/Vertices.hpp>

namespace randar
{
    struct Model : public Transformable
    {
        Vertices mesh;

        /**
         * Imports a model from a file.
         *
         * Only supports .obj files at the moment.
         */
        void import(std::string filename);
    };
}

#endif
