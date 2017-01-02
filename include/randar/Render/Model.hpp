#ifndef RANDAR_RENDER_MODEL_HPP
#define RANDAR_RENDER_MODEL_HPP

#include <randar/Engine/ResourceConsumer.hpp>
#include <randar/Physics/Physical.hpp>

namespace randar
{
    struct Model : virtual public Physical, virtual public ResourceConsumer
    {
        std::vector<Joint*> joints;

        ~Model();
    };
}

#endif
