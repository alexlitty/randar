#include <randar/Render/Shader.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructs a new uninitialized shader.
randar::Shader::Shader()
{

}

// Constructs a new shader as a copy of an existing one.
randar::Shader::Shader(const randar::Shader& other)
{
    *this = other;
}

// Constructs an initialized shader from in-memory code.
randar::Shader::Shader(
    ::GLenum initShaderType,
    const std::string& initCode)
: shaderType(initShaderType),
  code(initCode)
{
    this->gpu.initialize(*this);
}

// Destructor.
randar::Shader::~Shader() {
    this->gpu.destroy(*this);
}

// Assignment operator.
randar::Shader& randar::Shader::operator =(const randar::Shader& other)
{
    this->shaderType = other.shaderType;
    this->code = other.code;

    if (other.isInitialized()) {
        this->gpu.initialize(*this);
    }

    return *this;
}
