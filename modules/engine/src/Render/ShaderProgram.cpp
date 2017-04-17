#include <randar/Render/ShaderProgram.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructs a new shader program.
randar::ShaderProgram::ShaderProgram(Gpu* gpuInit)
: randar::GpuResource(gpuInit)
{
}

// Constructs a new shader program as a copy of an existing one.
randar::ShaderProgram::ShaderProgram(const randar::ShaderProgram& other)
{
    this->vertexShader = other.vertexShader;
    this->fragmentShader = other.fragmentShader;

    if (other.isInitialized()) {
        this->gpu->initialize(*this);
    }
}

// Constructs a shader program from existing shaders.
randar::ShaderProgram::ShaderProgram(
    randar::Shader& initVertexShader,
    randar::Shader& initFragmentShader)
: vertexShader(initVertexShader),
  fragmentShader(initFragmentShader)
{
    if (this->gpu) {
        this->gpu->initialize(*this);
    }
}

// Destructor.
randar::ShaderProgram::~ShaderProgram()
{
    if (this->gpu) {
        this->gpu->destroy(*this);
    }
}

// Sets the program shaders and initializes the program.
void randar::ShaderProgram::set(
    const randar::Shader& initVertexShader,
    const randar::Shader& initFragmentShader)
{
    if (this->isInitialized()) {
        this->gpu->destroy(*this);
    }

    this->vertexShader = initVertexShader;
    this->fragmentShader = initFragmentShader;
    if (this->gpu) {
        this->gpu->initialize(*this);
    }
}

// Checks if a uniform is used by the program.
bool randar::ShaderProgram::hasUniform(const std::string& name)
{
    if (this->gpu) {
        if (!this->uniformLocations.count(name)) {
            this->uniformLocations[name] = this->gpu->getUniformLocation(*this, name);
        }
    }

    return this->uniformLocations[name] >= 0;
}

// Sets a uniform to a 4x4 matrix.
void randar::ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix)
{
    if (this->gpu) {
        if (this->hasUniform(name)) {
            this->gpu->setUniform(*this, this->uniformLocations[name], matrix);
        }
    }
}

// Sets a uniform to an integer.
void randar::ShaderProgram::setUniform(const std::string& name, int integer)
{
    if (this->gpu) {
        if (this->hasUniform(name)) {
            this->gpu->setUniform(*this, this->uniformLocations[name], integer);
        }
    }
}

// Assignment operator.
randar::ShaderProgram& randar::ShaderProgram::operator =(const randar::ShaderProgram& other)
{
    this->gpu = other.gpu;
    this->set(other.vertexShader, other.fragmentShader);
    return *this;
}
