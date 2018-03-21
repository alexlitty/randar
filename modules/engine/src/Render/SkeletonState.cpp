#include <randar/Render/SkeletonState.hpp>

randar::SkeletonState::SkeletonState()
{

}

bool randar::SkeletonState::has(const std::string& name)
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
