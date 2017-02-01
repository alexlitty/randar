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

// Initializes the map with all possible uniforms.

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
