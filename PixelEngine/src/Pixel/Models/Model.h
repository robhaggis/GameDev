#pragma once

#include "Pixel/Shader.h"
#include "Pixel/Texture.h"

#include "Pixel/Core.h"
#include "glad.h"
#include "GLFW/glfw3.h"


namespace Pixel
{
	class AssetManager;
	class PIXEL_API Model
	{
	public:
		
		Model(AssetManager& assets, std::string name, const std::vector<f32>& vertices, const std::vector<ui32>& indices, std::string shaderName, std::vector<std::string> textureNames = {});
		virtual ~Model();

		inline void setShader(Shader* s) { m_Shader = s; }
		void addTexture(Texture* ts);

		template<typename T>
		void setUniform(std::string name, T value);
		
	public:
		std::string m_Name;
		AssetManager& m_AssetManager;

		Shader* m_Shader;
		std::vector<Texture*> m_Textures;
		
		ui32 m_VAO = 0, m_VBO = 0, m_EBO = 0;
		ui32 m_IndicesCount;

	};
}


