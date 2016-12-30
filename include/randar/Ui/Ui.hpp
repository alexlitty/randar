#ifndef RANDAR_UI_UI_HPP
#define RANDAR_UI_UI_HPP

#include <randar/Engine/ResourceConsumer.hpp>

namespace randar
{
    struct Ui : virtual public ResourceConsumer
    {
        Ui();
    };
}

#endif
