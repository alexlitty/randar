#include <randar/Ui/ResourcePatch.hpp>

randar::ResourcePatch::ResourcePatch(
    const std::string& initType,
    uint32_t initId,
    Json initJson)
: type(initType),
  id(initId),
  json(initJson)
{

}
