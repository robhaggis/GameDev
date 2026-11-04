#include "PixelPCH.h"
#include "Renderer.h"

namespace Pixel
{
	Renderer::Renderer()
		:m_VAO(0), m_VBO(0), m_EBO(0), m_IndicesCount(0)
	{}


	Renderer::~Renderer()
	{
	
		glDeleteBuffers(1, &m_EBO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}


	void Renderer::submit(const std::vector<f32>& vertices, const std::vector<ui32>& indices)
	{
		if (m_VAO == 0)
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			glGenBuffers(1, &m_EBO);
			
		}

		//Buffer Vertices
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(f32), vertices.data(), GL_STATIC_DRAW);
		
		//Buffer Indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(ui32), indices.data(), GL_STATIC_DRAW);
		m_IndicesCount = indices.size();

		//TODO Determine these vertex strides and indices etc at run time not hard coded like this
		//Position Attrib
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)0);
		glEnableVertexAttribArray(0);

		// TexCoord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(3 * sizeof(f32)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Renderer::flush(Shader* shader, Texture* texture1, Texture* texture2)
	{
		glUseProgram(shader->ID());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1->ID());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2->ID());
		glBindVertexArray(m_VAO);
		//glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
