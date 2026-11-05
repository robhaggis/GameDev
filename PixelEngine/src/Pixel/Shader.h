#pragma once

#include "Core.h"
#include "Log.h"
#include "glad.h"
#include "GLFW/glfw3.h"
#include "FileIO.h"

#include <glm/glm.hpp>

namespace Pixel
{
	class PIXEL_API Shader
	{
	public:
		Shader(std::string pathToVertShader, std::string pathToFragShader);
		~Shader();

		void bind();
		void unbind();
		inline const ui32 ID() { return m_ShaderID; }

		//Uniforms
		inline void setUniform(const std::string& name, bool value) const { glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), (int)value); }
		inline void setUniform(const std::string& name, i32 value) const { glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), value); }
		inline void setUniform(const std::string& name, f32 value) const { glUniform1f(glGetUniformLocation(m_ShaderID, name.c_str()), value); }

		inline void setUniform(const std::string& name, glm::vec2& vec) const { glUniform2fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, &vec[0]); }
		inline void setUniform(const std::string& name, glm::vec3& vec) const { glUniform3fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, &vec[0]); }
		inline void setUniform(const std::string& name, glm::vec4& vec) const { glUniform4fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, &vec[0]); }
		inline void setUniform(const std::string& name, f32 x, f32 y) const { glUniform2f(glGetUniformLocation(m_ShaderID, name.c_str()), x,y); }
		inline void setUniform(const std::string& name, f32 x, f32 y, f32 z) const { glUniform3f(glGetUniformLocation(m_ShaderID, name.c_str()), x,y,z); }
		inline void setUniform(const std::string& name, f32 x, f32 y, f32 z, f32 w) const { glUniform4f(glGetUniformLocation(m_ShaderID, name.c_str()), x,y,z,w); }
		
		inline void setUniform(const std::string& name, glm::mat2& mat) const { glUniformMatrix2fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);}
		inline void setUniform(const std::string& name, glm::mat3& mat) const { glUniformMatrix3fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);}
		inline void setUniform(const std::string& name, glm::mat4& mat) const { glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);}
	


	private:
		ui32 m_ShaderID = 0;

		void initTextureSlots();
	};
}

