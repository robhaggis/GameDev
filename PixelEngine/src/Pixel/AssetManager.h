#pragma once

#include "Core.h"
#include "Log.h"
#include "Shader.h"
#include "Texture.h"

namespace Pixel
{
	class PIXEL_API AssetManager
	{

	public:
		AssetManager();
		~AssetManager();
		void Init();

		void addShader(std::string name, std::string vertPath, std::string fragPath);
		Shader* getShader(std::string name);
		void deleteShader(std::string name);

		void addTexture(std::string name, std::string filepath);
		Texture* getTexture(std::string name);
		void deleteTexture(std::string name);
		
	private:

		std::unordered_map<std::string, Shader*>* m_ShaderPool;
		std::unordered_map<std::string, Texture*>* m_TexturePool;
	};
}

