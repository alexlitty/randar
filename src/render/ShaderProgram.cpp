#include <randar/render/ShaderProgram.hpp>

// Default constructor.
randar::ShaderProgram::ShaderProgram()
{

}

// Construct from existing shaders.
randar::ShaderProgram::ShaderProgram(randar::Shader &vertexShader, randar::Shader &fragmentShader)
{
    this->load(vertexShader, fragmentShader);
}

// Destructor.
randar::ShaderProgram::~ShaderProgram()
{
    ::glDeleteProgram(this->id);
}

// Links shaders together into a program.
void randar::ShaderProgram::load(randar::Shader &vertexShader, randar::Shader &fragmentShader)
{
    GLint linkStatus = GL_FALSE;
    int logLength;

    this->id = ::glCreateProgram();

    ::glAttachShader(this->id, vertexShader);
    ::glAttachShader(this->id, fragmentShader);
    ::glLinkProgram(this->id);

    ::glGetProgramiv(this->id, GL_LINK_STATUS, &linkStatus);
    ::glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &logLength);
    if (linkStatus == GL_FALSE) {
        if (logLength > 0) {
            GLchar *log = new char[logLength + 1];
            ::glGetProgramInfoLog(this->id, logLength, nullptr, log);
            throw std::runtime_error(log);
            delete[] log;
        }
    }

    ::glDetachShader(this->id, vertexShader);
    ::glDetachShader(this->id, fragmentShader);
}

// Convert to underlying OpenGL name.
randar::ShaderProgram::operator GLuint() const
{
    return this->id;
}
