#include <randar/Render/Shader.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructs a new uninitialized shader.
randar::Shader::Shader(randar::Gpu* gpuInit)
: randar::GpuResource(gpuInit)
{

}

// Constructs a new shader as a copy of an existing one.
randar::Shader::Shader(const randar::Shader& other)
: randar::GpuResource(other.gpu)
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
    if (this->gpu) {
        this->gpu->initialize(*this);
    }
}

// Destructor.
randar::Shader::~Shader() {
    if (this->gpu) {
        this->gpu->destroy(*this);
    }
}

// Assignment operator.
randar::Shader& randar::Shader::operator =(const randar::Shader& other)
{
    this->gpu = other.gpu;
    this->shaderType = other.shaderType;
    this->code = other.code;

    if (other.isInitialized()) {
        this->gpu->initialize(*this);
    }

    return *this;
}
