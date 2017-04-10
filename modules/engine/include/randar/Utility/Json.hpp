#ifndef RANDAR_UTILITY_JSON_HPP
#define RANDAR_UTILITY_JSON_HPP

#include <nlohmann/json.hpp>
using Json = nlohmann::json;

namespace randar
{
    template <typename T>
    Json toJson(const std::map<std::string, T*>& items)
    {
        Json result;
        for (auto item : items) {
            result[item.first] = item.second->toJson();
        }
        return result;
    }
}

#endif
