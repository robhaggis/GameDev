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

	void Renderer::submit(Model* model, glm::mat4 transform)
	{
		if (model)
		{
			RenderCommand cmd;
			cmd.VAO = model->m_VAO;
			cmd.shaderID = model->m_Shader->ID();
			cmd.transform = transform;
			cmd.modelMatrixShaderUniformLocation = glGetUniformLocation(cmd.shaderID, "model");

			for (i32 i = 0; i < model->m_Textures.size(); i++)
			{
				cmd.textureIDs.emplace_back(model->m_Textures.at(i)->ID());
			}

			m_RenderQueue.emplace_back(cmd);
		}
		
	}


	void Renderer::flush()
	{
		for (const RenderCommand& cmd : m_RenderQueue)
		{
			//Bind to model shader
			glUseProgram(cmd.shaderID);

			glUniformMatrix4fv(cmd.modelMatrixShaderUniformLocation, 1, GL_FALSE, &cmd.transform[0][0]);

			//Set Textures
			for (i32 i = 0; i < cmd.textureIDs.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, cmd.textureIDs.at(i));
			}

			//Bind to Vertex Array
			glBindVertexArray(cmd.VAO);

			glDrawArrays(GL_TRIANGLES, 0, 36);		//TODO Switch back to using DRAW_ELEMENTS indices and ebo
		}

		m_RenderQueue.clear();
	}
}
