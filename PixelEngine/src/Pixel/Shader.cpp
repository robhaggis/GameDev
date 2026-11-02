#include "PixelPCH.h"
#include "Shader.h"

Shader::Shader(const char* vertexSource, const char* fragmentSource)
{
    ui32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        PIX_CORE_ERROR("SHADER::VERTEX::COMPILATION_FAILED\n\n{0}", infoLog);
        return;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        PIX_CORE_ERROR("SHADER::FRAGMENT::COMPILATION_FAILED\n\n{0}", infoLog);
        return;
    }
    // link shaders
    m_ShaderID = glCreateProgram();
    glAttachShader(m_ShaderID, vertexShader);
    glAttachShader(m_ShaderID, fragmentShader);
    glLinkProgram(m_ShaderID);
    // check for linking errors
    glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ShaderID, 512, NULL, infoLog);
        PIX_CORE_ERROR("SHADER::LINKING_FAILED\n\n{0}", infoLog);
        return;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    PIX_CORE_INFO("Successfully Compiled Shader - ID{0}", m_ShaderID);
}

Shader::~Shader()
{
}


void Shader::use()
{
    glUseProgram(m_ShaderID);
}
