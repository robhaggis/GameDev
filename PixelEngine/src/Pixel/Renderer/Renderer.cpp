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
			glUseProgram(cmd.shaderID);


			//TODO Cache these uniform locations for each shader, so glGetUniformLocation isnt unneccessarily called on each flush
			const GLint viewLoc = glGetUniformLocation(cmd.shaderID, "view");
			if (viewLoc >= 0) glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &cmd.view[0][0]);
			
			const GLint projectionLoc = glGetUniformLocation(cmd.shaderID, "projection");
			if (projectionLoc >= 0) glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &cmd.projection[0][0]);
			
			const GLint modelLoc = glGetUniformLocation(cmd.shaderID, "model");
			if (modelLoc >= 0) glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &cmd.transform[0][0]);
			

			//Set Textures
			for (i32 i = 0; i < cmd.textureIDs.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, cmd.textureIDs.at(i)->ID());
			}

			//Bind to Vertex Array
			glBindVertexArray(cmd.VAO);

			glDrawElements(GL_TRIANGLES, cmd.indicesCount, GL_UNSIGNED_INT, 0);
		}

		m_RenderQueue.clear();
	}
}
