#pragma once

#include "Core.h"
#include "Log.h"
#include "glad.h"
#include "GLFW/glfw3.h"
#include "FileIO.h"

namespace Pixel
{
	class PIXEL_API Shader
	{
	public:
		Shader(std::string pathToVertShader, std::string pathToFragShader);
		~Shader();

		void use();
		inline const GLuint ID() { return m_ShaderID; }

	private:
		GLuint m_ShaderID = 0;
	};
}

