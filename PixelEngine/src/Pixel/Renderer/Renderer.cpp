#include "PixelPCH.h"
#include "Renderer.h"

namespace Pixel
{
	Renderer::Renderer()
	{
	
	}

	Renderer::~Renderer()
	{
	
		
	}

	void Renderer::submit(const RenderCommand& rc)
	{
		m_RenderQueue.emplace_back(rc);
	}

	void Renderer::flush()
	{
		for (const RenderCommand& cmd : m_RenderQueue)
		{
			//Bind to model shader
			glUseProgram(cmd.shader->ID());

			//Set Textures
			for (i32 i = 0; i < cmd.textureIDs.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, cmd.textureIDs.at(i)->ID());
			}

			//Set Uniforms
			for (const Uniform& u : cmd.uniforms)
			{
				//TODO WTF? Make this more elegant
				if (const bool* value = std::get_if<bool>(&u.value)) cmd.shader->setUniform(u.name, *value);
				else if (const i32* value = std::get_if<i32>(&u.value)) cmd.shader->setUniform(u.name, *value);
				else if (const f32* value = std::get_if<f32>(&u.value)) cmd.shader->setUniform(u.name, *value);
				else if (const glm::vec2* value = std::get_if<glm::vec2>(&u.value)) cmd.shader->setUniform(u.name, *value);
				else if (const glm::vec3* value = std::get_if<glm::vec3>(&u.value)) cmd.shader->setUniform(u.name, *value);
				else if (const glm::vec4* value = std::get_if<glm::vec4>(&u.value)) cmd.shader->setUniform(u.name, *value);
				else if (const glm::mat2* value = std::get_if<glm::mat2>(&u.value)) cmd.shader->setUniform(u.name, *value);
				else if (const glm::mat3* value = std::get_if<glm::mat3>(&u.value)) cmd.shader->setUniform(u.name, *value);
				else if (const glm::mat4* value = std::get_if<glm::mat4>(&u.value)) cmd.shader->setUniform(u.name, *value);

			}

			//Bind to Vertex Array
			glBindVertexArray(cmd.VAO);

			glDrawElements(GL_TRIANGLES, cmd.indicesCount, GL_UNSIGNED_INT, 0);
		}

		m_RenderQueue.clear();
	}
}
