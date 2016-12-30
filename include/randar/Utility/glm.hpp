#ifndef RANDAR_UTILITY_GLM_HPP
#define RANDAR_UTILITY_GLM_HPP

#define GLM_FORCE_RADIANS

#include <string>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace randar
{
    glm::mat3x4 toMat3x4(const glm::mat4& matrix);
    std::string toString(glm::mat4 matrix);
}

#endif
