#ifndef RANDAR_RENDER_SKELETON_HPP
#define RANDAR_RENDER_SKELETON_HPP

#include <map>
#include <vector>
#include <randar/Render/Joint.hpp>

namespace randar
{
    /**
     * Skeleton for models to represent joint states.
     */
    class Skeleton
    {
        /**
         * Joints in the skeleton.
         */
        std::vector<Joint> joints;

        /**
         * Names of joints in the skeleton.
         */
        std::vector<std::string> jointNames;

        /**
         * Map of joint parents.
         */
        std::map<uint32_t, uint32_t> jointParents;

    public:
        /**
         * Default constructor.
         */
        Skeleton();

        /**
         * Assignment.
         */
        Skeleton(const Skeleton& other);
        Skeleton& operator =(const Skeleton& other);
        Skeleton(Skeleton&& other);

        /**
         * Destructor.
         */
        ~Skeleton();

        /**
         * Clears the joints on the skeleton.
         */
        void clear();

        /**
         * Adds a parentless joint to the skeleton, returning the added joint.
         *
         * Throws an error if a joint with the same name already exists.
         */
        Joint& add(const std::string& name);

        /**
         * Adds a child joint to the skeleton, returning the added joint.
         *
         * Throws an error if a joint with the same name already exists, or a
         * joint with the desired parent name does not exist.
         */
        Joint& add(const std::string& name, const std::string& parentName);

        /**
         * Counts the joints on the skeleton.
         */
        uint32_t jointCount() const;

        /**
         * Retrieves a joint by name or index.
         *
         * Throws an error if the joint does not exist.
         */
        Joint& joint(const std::string& name);
        Joint& joint(uint32_t index);

        /**
         * Retrieves the name of a joint by its index.
         *
         * Throws an error if the joint does not exist.
         */
        std::string jointName(uint32_t index) const;

        /**
         * Whether a named joint exists in the skeleton.
         *
         * @@@ horribly inefficient because of class structure. use better
         * data structures.
         */
        bool hasJoint(const std::string& name) const;

        /**
         * Retrieves the index of a joint by its name.
         *
         * Throws an error if the joint does not exist.
         */
        uint32_t jointIndex(const std::string& name) const;

        /**
         * Calculates the matrix of a joint and its parents.
         *
         * Throws an error if the joint does not exist.
         */
        glm::mat4 matrix(const std::string& name);
        glm::mat4 matrix(uint32_t index);
    };

    /**
     * Node.js helper.
     */
    Skeleton skeleton();
}

#endif
