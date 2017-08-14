#include <randar/Render/Skeleton.hpp>

// Default constructor.
randar::Skeleton::Skeleton()
{

}

// Assignment.
randar::Skeleton::Skeleton(const randar::Skeleton& other)
{
    *this = other;
}

randar::Skeleton& randar::Skeleton::operator =(const randar::Skeleton& other)
{
    this->clear();

    this->joints = other.joints;
    this->jointNames = other.jointNames;
    this->jointParents = other.jointParents;

    return *this;
}

randar::Skeleton::Skeleton(randar::Skeleton&& other)
{
    *this = other;
    other.clear();
}

// Destructor.
randar::Skeleton::~Skeleton()
{
    this->clear();
}

// Clears the joints on the skeleton.
void randar::Skeleton::clear()
{
    this->joints.clear();
    this->jointNames.clear();
    this->jointParents.clear();
}

// Adds a parentless joint to the skeleton.
randar::Joint& randar::Skeleton::add(const std::string& name)
{
    this->joints.emplace_back();
    this->jointNames.push_back(name);
    return this->joints[this->joints.size() - 1];
}

// Adds a child joint to the skeleton.
randar::Joint& randar::Skeleton::add(const std::string& name, const std::string& parentName)
{
    randar::Joint& joint = this->add(name);
    this->jointParents[this->joints.size() - 1] = this->jointIndex(parentName);
    return joint;
}

// Counts the joints on the skeleton.
uint32_t randar::Skeleton::jointCount() const
{
    return this->joints.size();
}

// Retrieves a joint by its name or index.
randar::Joint& randar::Skeleton::joint(const std::string& name)
{
    return this->joint(this->jointIndex(name));
}

randar::Joint& randar::Skeleton::joint(uint32_t index)
{
    if (index >= this->jointNames.size()) {
        throw new std::runtime_error("Joint does not exist");
    }

    return this->joints[index];
}

// Retrieves the name of a joint by its index.
std::string randar::Skeleton::jointName(uint32_t index) const
{
    if (index >= this->jointNames.size()) {
        throw new std::runtime_error("Joint does not exist");
    }

    return this->jointNames[index];
}

// Retrieves the index of a joint by its name.
uint32_t randar::Skeleton::jointIndex(const std::string& name) const
{
    for (uint32_t i = 0; i < this->jointNames.size(); i++) {
        if (this->jointNames[i] == name) {
            return i;
        }
    }

    throw new std::runtime_error("Joint does not exist");
}

// Calculates the matrix of a joint and its parents.
glm::mat4 randar::Skeleton::matrix(const std::string& name)
{
    return this->matrix(this->jointIndex(name));
}

glm::mat4 randar::Skeleton::matrix(uint32_t index)
{
    randar::Joint& joint = this->joint(index);

    if (!this->jointParents.count(index)) {
        return joint.transformMatrix();
    }

    return joint.transformMatrix() * this->matrix(this->jointParents[index]);
}

// Node.js helper.
randar::Skeleton randar::skeleton()
{
    return randar::Skeleton();
}
