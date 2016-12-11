#include <randar/utility/glm.hpp>

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
