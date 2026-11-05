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

	void Renderer::submit(Model* model)
	{
		m_RenderQueue.emplace_back(model);
	}


	void Renderer::flush()
	{

		/*
		
			m_VAO
			m_TextureIDs
			m_Shader

		
		*/
		for (Model* model : m_RenderQueue)
		{
			//Bind to model shader
			glUseProgram(model->m_Shader->ID());

			//Set Textures
			for (i32 i = 0; i < model->m_Textures.size(); i++)
			{
				PIX_CORE_ASSERT(i < 16, "Too many textures, MAX 16");
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, model->m_Textures.at(i)->ID());
			}

			//Bind to Vertex Array
			glBindVertexArray(model->m_VAO);

			glDrawArrays(GL_TRIANGLES, 0, 36);		//TODO Switch back to using DRAW_ELEMENTS indices and ebo
		}

		//m_RenderQueue.clear();
	}
}
