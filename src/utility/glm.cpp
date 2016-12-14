#include <randar/utility/glm.hpp>

glm::mat3x4 randar::toMat3x4(const glm::mat4& matrix)
{
    return glm::make_mat3x4(static_cast<const float*>(glm::value_ptr(matrix)));
}

std::string randar::toString(glm::mat4 matrix)
{
    std::string str;
    const float* values = static_cast<const float*>(glm::value_ptr(matrix));

    for (unsigned int i = 0; i < 16; i++) {
        if (i == 4 || i == 8 || i == 12) {
            str += "\n  ";
        }
        str += std::to_string(values[i]) + " ";
    }

    return "[ " + str + "]";
}
