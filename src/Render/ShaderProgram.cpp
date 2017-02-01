#include <randar/Render/ShaderProgram.hpp>
#include <randar/Engine/Gpu.hpp>

// Constructs a new shader program.
randar::ShaderProgram::ShaderProgram()
{
}

// Constructs a new shader program as a copy of an existing one.
randar::ShaderProgram::ShaderProgram(const randar::ShaderProgram& other)
{
    this->vertexShader = other.vertexShader;
    this->fragmentShader = other.fragmentShader;

    if (other.isInitialized()) {
        this->gpu.initialize(*this);
    }
}

// Constructs a shader program from existing shaders.
randar::ShaderProgram::ShaderProgram(
    randar::Shader& initVertexShader,
    randar::Shader& initFragmentShader)
: vertexShader(initVertexShader),
  fragmentShader(initFragmentShader)
{
    this->gpu.initialize(*this);
}

// Destructor.
randar::ShaderProgram::~ShaderProgram()
{
    this->gpu.destroy(*this);
}

// Sets the program shaders and initializes the program.
void randar::ShaderProgram::set(
    const randar::Shader& initVertexShader,
    const randar::Shader& initFragmentShader)
{
    if (this->isInitialized()) {
        this->gpu.destroy(*this);
    }

    this->vertexShader = initVertexShader;
    this->fragmentShader = initFragmentShader;
    this->gpu.initialize(*this);
}

void randar::ShaderProgram::setUniformLocation(const std::string& name, ::GLint location)
{
    if (this->uniformLocations.count(name)) {
        throw std::runtime_error(
            "Setting " + name + " uniform location of "
            + std::to_string(location)
            + ", but already set as "
            + std::to_string(this->uniformLocations[name])
        );
    }

    this->uniformLocations[name] = location;
}

// Checks if this program uses a uniform.
bool randar::ShaderProgram::hasUniform(const std::string& name) const
{
    return this->uniformLocations.count(name) == 1;
}

// Writes a value to a uniform.
void randar::ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix)
{
    if (this->hasUniform(name)) {
        this->gpu.setUniform(*this, this->uniformLocations[name], matrix);
    }
}
