#include <randar/Render/SkeletonState.hpp>

bool randar::SkeletonState::hasJoint(const std::string& name)
{
    return this->joints.count(name);
}

randar::Joint& randar::SkeletonState::joint(const std::string& name)
{
    return this->joints[name];
}

void randar::SkeletonState::remove(const std::string& name)
{
    this->joints.erase(name);
}
