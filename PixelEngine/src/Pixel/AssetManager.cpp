#include "PixelPCH.h"
#include "AssetManager.h"

namespace Pixel
{
	AssetManager::AssetManager()
		:m_ShaderPool(nullptr), m_TexturePool(nullptr)
	{
		m_ShaderPool = new std::unordered_map<std::string, Shader*>;
		m_TexturePool = new std::unordered_map<std::string, Texture*>;
	}

	AssetManager::~AssetManager()
	{
		delete m_ShaderPool;
		delete m_TexturePool;
	}

	void AssetManager::addShader(std::string name, std::string vertPath, std::string fragPath)
	{
		auto it = m_ShaderPool->find(name);

		if (it == m_ShaderPool->end())
		{
			Shader* s = new Shader(vertPath, fragPath);
			m_ShaderPool->insert({ name, s });
			PIX_CORE_INFO("Added new Shader to asset pool with name {0}, m_ShaderID({1})", name, s->ID());
		}
		else
		{
			PIX_CORE_WARN("Shader already exists with name {0}. Skipping...", name);
		}
	}
	Shader* AssetManager::getShader(std::string name)
	{
		if (m_ShaderPool == nullptr)
		{
			PIX_CORE_WARN("Shader Pool not initialized");
			return nullptr;
		}

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
		}
		else
		{
			PIX_CORE_WARN("Could not find shader with name {0}. No Deletion Occured", name);
			return;
		}
	}

	void AssetManager::addTexture(std::string name, std::string filepath)
	{
		auto it = m_TexturePool->find(name);

		if (it == m_TexturePool->end())
		{
			Texture* t = new Texture(filepath);
			m_TexturePool->insert({ name, t });
			PIX_CORE_INFO("Added new Texture to asset pool with name {0}, m_TextureID({1})", name, t->ID());
		}
		else
		{
			PIX_CORE_WARN("Texture already exists with name {0}. Skipping...", name);
		}
	}

	Texture* AssetManager::getTexture(std::string name)
	{
		if (m_TexturePool == nullptr)
		{
			PIX_CORE_WARN("Texture Pool not initialized");
			return nullptr;
		}

		auto it = m_TexturePool->find(name);
		if (it != m_TexturePool->end())
		{
			return it->second;
		}
		else
		{
			PIX_CORE_WARN("Could not find texture with name {0}. Skipping...", name);
			return nullptr; //TODO - Add a default texture to the texture pool which we can return by default
		}
	}
	void AssetManager::deleteTexture(std::string name)
	{
		auto it = m_TexturePool->find(name);
		if (it != m_TexturePool->end())
		{
			delete it->second;
			m_TexturePool->erase(it);
		}
		else
		{
			PIX_CORE_WARN("Could not find Texture with name {0}. No Deletion Occured", name);
			return;
		}
	}

}


