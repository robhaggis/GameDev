#include "PixelPCH.h"
#include "Shader.h"

namespace Pixel
{


    Shader::Shader(std::string pathToVertShader, std::string pathToFragShader)
        :m_ShaderID(0)
    {

        std::string vertStr = FileIO::readStringFromFile(pathToVertShader);
        std::string fragStr = FileIO::readStringFromFile(pathToFragShader);

        const char* vertexSource = vertStr.c_str();
        const char* fragmentSource = fragStr.c_str();

        ui32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[1024] = {};
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
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
            glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
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
            glGetProgramInfoLog(m_ShaderID, 1024, NULL, infoLog);
            PIX_CORE_ERROR("SHADER::LINKING_FAILED\n\n{0}", infoLog);
            return;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        PIX_CORE_INFO("Successfully Compiled Shader - ID{0}", m_ShaderID);
        vertStr.clear();
        fragStr.clear();

    }

    Shader::~Shader()
    {}


    void Shader::use()
    {
        glUseProgram(m_ShaderID);
    }

}