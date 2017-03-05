#ifndef RANDAR_UI_RESOURCE_PATCH_HPP
#define RANDAR_UI_RESOURCE_PATCH_HPP

#include <randar/Utility/Json.hpp>

namespace randar
{
    struct ResourcePatch
    {
        std::string type;
        uint32_t id;
        Json json;

        ResourcePatch(
            const std::string& initType,
            uint32_t initId,
            Json initJson);
    };
}

#endif
