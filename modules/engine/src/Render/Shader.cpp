#include <randar/Render/Shader.hpp>
#include <randar/Utility/String.hpp>

// Default constructor.
randar::Shader::Shader()
: randar::GraphicsContextResource(nullptr)
{

}

// Primary constructor.
randar::Shader::Shader(GraphicsContext& context)
: randar::GraphicsContextResource(&context)
{

}

// Destructor.
randar::Shader::~Shader() {
    this->uninitialize();
}

// Sets the context to initialize the shader with.
void randar::Shader::context(randar::GraphicsContext& newContext)
{
    this->uninitialize();
    this->ctx = &newContext;
}

// Initializes the shader.
void randar::Shader::initialize()
{
    GLint compileStatus, logLength;
    this->uninitialize();

    if (!this->ctx) {
        throw std::runtime_error("Shader has no graphics context assigned");
    }
    this->ctx->use();

    // Create the shader.
    this->glName = ::glCreateShader(this->glType());
    this->ctx->check("Cannot create shader");
    if (!this->glName) {
        throw std::runtime_error("Failed to create shader");
    }

    // Compile.
    const char *rawCode = this->shaderCode.c_str();
    ::glShaderSource(this->glName, 1, &rawCode, nullptr);
    ::glCompileShader(this->glName);
    this->ctx->check("Cannot compile shader");

    // Check compilation.
    ::glGetShaderiv(this->glName, GL_COMPILE_STATUS, &compileStatus);
    ::glGetShaderiv(this->glName, GL_INFO_LOG_LENGTH, &logLength);
    
    if (compileStatus == GL_FALSE) {
        std::string message = "Shader compilation failed: ";

        if (logLength > 0) {
            GLchar *log = new char[logLength + 1];

            ::glGetShaderInfoLog(this->glName, logLength, nullptr, log);
            message += std::string(log);

            delete[] log;
        } else {
            message += "No log available";
        }

        throw std::runtime_error(message);
    }
}

void randar::Shader::initialize(
    randar::Shader::Type newType,
    const std::string& newCode)
{
    this->shaderType = newType;
    this->shaderCode = newCode;
    this->initialize();
}

void randar::Shader::initialize(
    std::string newType,
    const std::string& newCode)
{
    Shader::Type randarType;

    newType = randar::toLowercase(newType);
    if (newType == "vertex") {
        randarType = Shader::Type::Vertex;
    } else if (newType == "fragment") {
        randarType = Shader::Type::Fragment;
    } else {
        throw std::runtime_error("Invalid shader type");
    }

    this->initialize(randarType, newCode);
}

// Uninitializes the shader.
void randar::Shader::uninitialize()
{
    if (!this->isInitialized()) {
        return;
    }

    this->ctx->use();
    ::glDeleteShader(this->glName);
    this->glName = 0;
}

// Whether the shader is initialized.
bool randar::Shader::isInitialized() const
{
    return this->ctx && this->glName;
}

// Retrieves the shader type.
randar::Shader::Type randar::Shader::type() const
{
    return this->shaderType;
}

GLenum randar::Shader::glType() const
{
    switch (this->shaderType) {
        case Shader::Type::Vertex:
            return GL_VERTEX_SHADER;

        case Shader::Type::Fragment:
            return GL_FRAGMENT_SHADER;

        default:
            throw std::runtime_error("Shader has invalid type");
    }
}
