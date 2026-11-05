#include "Model.h"
#include "PixelPCH.h"
#include "Model.h"

#include "AssetManager.h"

namespace Pixel

{
	Model::Model(AssetManager& assets, std::string name, const std::vector<f32>& vertices, const std::vector<ui32>& indices, std::string shaderName, std::vector<std::string> textureNames)
		:m_Name(name), 
		m_AssetManager(assets),
		m_Shader(assets.getShader(shaderName))
	{

		if (!assets.isInitialized()) assets.Init();		//Sanity Check

		//If textures provided to the constructor, then set them to default texture (#FF00FF)
		if (textureNames.empty())
		{
			m_Textures.emplace_back(assets.getTexture("defaultTexture"));
		}
		else
		{
			for (std::string s :textureNames)
			{
				m_Textures.emplace_back(assets.getTexture(s));
			}
		}

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

		//Add default texture and shader
		//TODO
	}

	Model::~Model()
	{
		glDeleteBuffers(1, &m_EBO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void Model::addTexture(Texture* t)
	{
		if (m_Textures.size() < 16)
		{
			m_Textures.emplace_back(t);
		}
		else
		{
			PIX_CORE_WARN("Texture limit is 16 per model, numer of textures in model '{0}' is {1}. Texture Not Added", m_Name, m_Textures.size());
		}
	}
}
