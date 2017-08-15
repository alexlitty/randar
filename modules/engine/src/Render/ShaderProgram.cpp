#include <randar/Render/ShaderProgram.hpp>

// Constructor.
randar::ShaderProgram::ShaderProgram(randar::GraphicsContext& context)
: randar::GraphicsContextResource(&context)
{

}

// Destructor.
randar::ShaderProgram::~ShaderProgram()
{
    this->uninitialize();
}

// Whether this program is complete and linkable.
bool randar::ShaderProgram::isComplete() const
{
    if (!this->shaders.count(ShaderType::VERTEX)) {
        return false;
    }

    if (!this->shaders.count(ShaderType::FRAGMENT)) {
        return false;
    }

    return true;
}

// Initializes the program.
void randar::ShaderProgram::initialize()
{
    GLint linkStatus, logLength;
    this->uninitialize();

    if (!this->isComplete()) {
        throw std::runtime_error("Shader program is incomplete");
    }

    if (!this->ctx) {
        throw std::runtime_error("Graphics context unavailable");
    }
    this->ctx->use();

    // Create the program.
    this->glName = ::glCreateProgram();
    this->ctx->check("Cannot create shader program");
    if (!this->glName) {
        throw std::runtime_error("Failed to create shader program");
    }

    // Link shaders.
    for (auto item : this->shaders) {
        ::glAttachShader(this->glName, item.second->getGlName());
    }
    ::glLinkProgram(this->glName);
    this->ctx->check("Cannot link shader program");

    for (auto item : this->shaders) {
        ::glDetachShader(this->glName, item.second->getGlName());
    }

    // Check linkage.
    ::glGetProgramiv(this->glName, GL_LINK_STATUS, &linkStatus);
    ::glGetProgramiv(this->glName, GL_INFO_LOG_LENGTH, &logLength);
    if (linkStatus == GL_FALSE) {
        std::string message = "Shader program linking failed: ";

        if (logLength > 0) {
            GLchar *log = new char[logLength + 1];

            ::glGetProgramInfoLog(this->glName, logLength, nullptr, log);
            message += std::string(log);

            delete[] log;
        } else {
            message += "No log available";
        }

        throw std::runtime_error(message);
    }
}

// Uninitializes the program.
void randar::ShaderProgram::uninitialize()
{
    if (!this->isInitialized()) {
        return;
    }

    this->ctx->use();
    ::glDeleteProgram(this->glName);
    this->glName = 0;

    this->uniformLocations.clear();
}

// Whether the program is initialized.
bool randar::ShaderProgram::isInitialized() const
{
    return this->ctx && this->glName;
}

// Uses this program for further operations.
void randar::ShaderProgram::use()
{
    if (!this->isInitialized()) {
        this->initialize();
    }

    if (!this->inSync) {
        this->initialize();
        this->inSync = true;
    }

    this->ctx->use();
    ::glUseProgram(this->glName);
}

// Attaches a shader to the program.
void randar::ShaderProgram::attach(randar::Shader& shader)
{
    this->shaders[shader.type()] = &shader;
    this->inSync = false;
}

// Checks if a uniform is used by the program.
bool randar::ShaderProgram::hasUniform(const std::string& name)
{
    if (!this->uniformLocations.count(name)) {
        this->use();
        int location = ::glGetUniformLocation(this->glName, name.c_str());

        this->ctx->check("Cannot query uniform location");
        this->uniformLocations[name] = location;
    }

    return this->uniformLocations[name] >= 0;
}

// Sets a uniform to a 4x4 matrix.
void randar::ShaderProgram::uniform(const std::string& name, const glm::mat4& matrix)
{
    if (this->hasUniform(name)) {
        this->use();

        ::glUniformMatrix4fv(
            this->uniformLocations[name],
            1,
            GL_FALSE,
            &matrix[0][0]
        );
    }
}

void randar::ShaderProgram::uniform(const std::string& name, const std::vector<glm::mat4>& matrices)
{
    if (!matrices.size()) {
        return;
    }

    if (this->hasUniform(name)) {
        this->use();

        ::glUniformMatrix4fv(
            this->uniformLocations[name],
            matrices.size(),
            GL_FALSE,
            glm::value_ptr(matrices[0])
        );
    }
}

// Sets a uniform to an integer.
void randar::ShaderProgram::uniform(const std::string& name, int integer)
{
    if (this->hasUniform(name)) {
        this->use();

        ::glUniform1i(this->uniformLocations[name], integer);
    }
}
