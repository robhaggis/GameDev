#pragma once

#include "Core.h"
#include "Log.h"
#include "glad.h"
#include "GLFW/glfw3.h"

class PIXEL_API Shader
{
public:
	Shader(const char* vertexSource, const char* fragmentSource);
	~Shader();

	void use();
	inline const GLuint ID() { return m_ShaderID; }

private:
	GLuint m_ShaderID = 0;
};

