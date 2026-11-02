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

		//Uniforms
		inline void setUniform(const std::string& name, bool value) const { glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), (int)value); }
		inline void setUniform(const std::string& name, i32 value) const { glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), value); }
		inline void setUniform(const std::string& name, f32 value) const { glUniform1f(glGetUniformLocation(m_ShaderID, name.c_str()), value); }


	private:
		GLuint m_ShaderID = 0;
	};
}

