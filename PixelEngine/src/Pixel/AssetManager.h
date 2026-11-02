#pragma once

#include "Core.h"
#include "Log.h"
#include "Shader.h"

namespace Pixel
{
	class AssetManager
	{

	public:
		AssetManager();
		~AssetManager();

		void addShader(std::string name, std::string vertPath, std::string fragPath);
		Shader* getShader(std::string name);
		void deleteShader(std::string name);
		
	private:

		std::unordered_map<std::string, Shader*>* m_ShaderPool;
		ui32 m_ShaderCount;

	};
}

