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
			cmd.modelLoc = glGetUniformLocation(cmd.shaderID, "model");

			for (i32 i = 0; i < model->m_Textures.size(); i++)
			{
				cmd.textureIDs.emplace_back(model->m_Textures.at(i)->ID());
			}

			m_RenderQueue.emplace_back(cmd);
		}
		
	}


	void Renderer::flush(const glm::mat4& view, const glm::mat4& projection)
	{
		for (const RenderCommand& cmd : m_RenderQueue)
		{
			//Bind to model shader
			glUseProgram(cmd.shaderID);

			const GLint viewLoc = glGetUniformLocation(cmd.shaderID, "view");
			const GLint projectionLoc = glGetUniformLocation(cmd.shaderID, "projection");
			
			if (viewLoc >= 0) glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

			if (projectionLoc >= 0) glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);


			if (cmd.modelLoc >= 0)glUniformMatrix4fv(cmd.modelLoc, 1, GL_FALSE, &cmd.transform[0][0]);

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
