#ifndef RANDAR_UTILITY_VECTOR_HPP
#define RANDAR_UTILITY_VECTOR_HPP

#include <vector>

namespace randar
{
    template <typename T>
    Json toJson(const std::vector<T*>& vector)
    {
        Json result;
        for (auto item : vector) {
            result.push_back(item->toJson());
        }
        return result;
    }
}

#endif
