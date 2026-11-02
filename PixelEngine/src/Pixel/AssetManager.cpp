#include "PixelPCH.h"
#include "AssetManager.h"

namespace Pixel
{
	AssetManager::AssetManager()
		:m_ShaderPool(nullptr), m_ShaderCount(0)
	{
		m_ShaderPool = new std::unordered_map<std::string, Shader*>;
	}

	AssetManager::~AssetManager()
	{
		delete m_ShaderPool;
	}
	void AssetManager::addShader(std::string name, std::string vertPath, std::string fragPath)
	{
		auto it = m_ShaderPool->find(name);

		if (it == m_ShaderPool->end())
		{
			Shader* s = new Shader(vertPath, fragPath);
			m_ShaderPool->insert({ name, s });
			m_ShaderCount++;
			PIX_CORE_INFO("Addded new Shader to asset pool with name {0}, m_ShaderID({1})", name, s->ID());
		}
		else
		{
			PIX_CORE_WARN("Shader already exists with name {0}. Skipping...", name);
		}
	}
	Shader* AssetManager::getShader(std::string name)
	{
		auto it = m_ShaderPool->find(name);
		if (it != m_ShaderPool->end())
		{
			return it->second;
		}
		else
		{
			PIX_CORE_WARN("Could not find shader with name {0}. Skipping...", name);
			return nullptr; //TODO - Add a default shader to the shader pool which we can return by default
		}
	}
	void AssetManager::deleteShader(std::string name)
	{
		auto it = m_ShaderPool->find(name);
		if (it != m_ShaderPool->end())
		{
			delete it->second;
			m_ShaderPool->erase(it);
			m_ShaderCount--;
		}
		else
		{
			PIX_CORE_WARN("Could not find shader with name {0}. No Deletion Occured", name);
			return;
		}
	}
}


