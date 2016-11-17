#include <randar/render/Shader.hpp>

randar::Shader::Shader(std::string file, GLenum initType)
: type(initType)
{
    std::ifstream stream(file, std::ios::in);
    if (!stream.is_open()) {
        throw new std::runtime_error("Cannot load shader: " + file);
    }

    // Read the code from the file.
    std::string code;
    std::string line;
    while (std::getline(stream, line)) {
        code += "\n" + line;
    }
    stream.close();

    // Compile the shader.
    char const *codeData = code.c_str();
    GLint compileStatus = GL_FALSE;
    int logLength;

    this->id = ::glCreateShader(this->type);
    ::glShaderSource(this->id, 1, &codeData, nullptr);
    ::glCompileShader(this->id);

    ::glGetShaderiv(this->id, GL_COMPILE_STATUS, &compileStatus);
    ::glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &logLength);
    if (compileStatus == GL_FALSE) {
        if (logLength > 0) {
            GLchar *log = new char[logLength + 1];
            ::glGetShaderInfoLog(this->id, logLength, nullptr, log);
            throw std::runtime_error(log);
            delete[] log;
        } else {
            throw std::runtime_error("Cannot compile shader, no log available: " + file);
        }
    }
}

randar::Shader::~Shader()
{
    ::glDeleteShader(this->id);
}

randar::Shader::operator GLuint() const
{
    return this->id;
}
