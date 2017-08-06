#include <map>
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
    randar::ShaderType newType,
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
    ShaderType randarType;

    newType = randar::toLowercase(newType);
    if (newType == "vertex") {
        randarType = ShaderType::VERTEX;
    } else if (newType == "fragment") {
        randarType = ShaderType::FRAGMENT;
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
randar::ShaderType randar::Shader::type() const
{
    return this->shaderType;
}

GLenum randar::Shader::glType() const
{
    switch (this->shaderType) {
        case ShaderType::VERTEX:
            return GL_VERTEX_SHADER;

        case ShaderType::FRAGMENT:
            return GL_FRAGMENT_SHADER;

        default:
            throw std::runtime_error("Shader has invalid type");
    }
}

// Generates the code for a default shader.
std::string randar::Shader::defaultCode(randar::ShaderType type)
{
    static std::map<ShaderType, std::string> codes = {
        {
            ShaderType::VERTEX,
            R"SHADER(#version 450 core
                layout(location = 0) in vec3 vertexPosition;
                layout(location = 1) in vec4 vertexColor;
                layout(location = 2) in vec3 vertexNormal;
                layout(location = 3) in int  vertexTextureId;
                layout(location = 4) in vec2 vertexUV;
                out vec4 lightPosition0;
                out vec4 fragmentColor;
                out int  geoTextureId;
                out vec2 uv;

                uniform mat4 projectionMatrix;
                uniform mat4 viewMatrix;
                uniform mat4 modelMatrix;

                uniform mat4 lightMatrix0;

                void main()
                {
                    gl_Position = projectionMatrix
                                * viewMatrix
                                * modelMatrix
                                * vec4(vertexPosition, 1.0);
                    fragmentColor = vertexColor;

                    vec3 fragPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0));
                    lightPosition0 = lightMatrix0 * vec4(fragPosition, 1.0);

                    geoTextureId = vertexTextureId;
                    uv = vertexUV;
                }
            )SHADER"
        },

        {
            ShaderType::FRAGMENT,
            R"SHADER(#version 450 core
                in vec4 lightPosition0;
                in vec4 fragmentColor;
                flat in int geoTextureId;
                in vec2 uv;

                out vec4 color;
                out float fragmentDepth;

                uniform sampler2D geoTexture0;
                uniform int lightsEnabled;
                uniform sampler2D lightmap0;

                float shadowPower(vec4 lightPosition, sampler2D lightmap)
                {
                    if (lightsEnabled == 0) {
                        return 1.0f;
                    }

                    vec3 projCoords = lightPosition.xyz / lightPosition.w;
                    float closestDepth = texture(lightmap, projCoords.xy).r;
                    float currentDepth = projCoords.z;
                    return currentDepth - 0.05 > closestDepth ? 1.0f : 0.5f;
                }

                void main()
                {
                    float visibility = shadowPower(lightPosition0, lightmap0);

                    if (geoTextureId == 0) {
                        color = texture(geoTexture0, uv).rgba;
                    }
                    
                    else {
                        color = fragmentColor;
                    }

                    color = vec4((visibility * color).rgb, color.a);
                }
            )SHADER"
        }
    };

    if (!codes.count(type)) {
        throw std::runtime_error("Default code not available for shader type");
    }

    return codes[type];
}
