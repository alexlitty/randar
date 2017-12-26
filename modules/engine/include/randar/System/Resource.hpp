#pragma once

#include <string>

namespace randar
{
    class Resource
    {
    public:
        virtual ~Resource();
        virtual std::string description() = 0;
        void describe();
    };
}
