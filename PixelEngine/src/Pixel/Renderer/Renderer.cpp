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
			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(f32), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(ui32), indices.data(), GL_STATIC_DRAW);
		m_IndicesCount = indices.size();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Renderer::flush(GLuint shaderID)
	{
		glUseProgram(shaderID);
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, 0);
	}
}
