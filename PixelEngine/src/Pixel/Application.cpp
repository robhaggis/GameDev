#include "PixelPCH.h"
#include "Application.h"

namespace Pixel
{
	Application::Application(i32 width, i32 height, const char* title)
		:m_Window(nullptr), m_Renderer(nullptr)
	{
		m_Window.reset(Window::create(width, height, title));
		m_assetManager.Init();
		m_Renderer = new Renderer();
	}

	Application::~Application()
	{
		m_LayerStack.RemoveAllLayers();
		delete m_Renderer;
	}

	void Application::run()
	{
		while (m_isRunning && !m_Window->windowShouldClose())
		{
			m_Window->processInput(&m_InputData);

			if (m_InputData.isKeyJustPressed[GLFW_KEY_ESCAPE])
			{
				m_Window->toggleMouseCapture();
			}

			m_Window->clear();

			for (Layer* layer : m_LayerStack)
			{
				if (layer->isEnabled())
				{
					layer->OnUpdate();
					layer->processInput(&m_InputData);
				}
			}
			m_Window->update();
		}
		m_isRunning = false;
	}

	void Application::PushLayer(Layer* layer)
	{
		layer->setAssetManager(&m_assetManager);
		layer->setRenderer(m_Renderer);
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLay(Layer * overlay)
	{
		overlay->setAssetManager(&m_assetManager);
		overlay->setRenderer(m_Renderer);
		m_LayerStack.PushLayer(overlay);
		overlay->OnAttach();
	}

	void Application::PopLayer(Layer* layer)
	{
		layer->OnDetach();
		m_LayerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer * overlay)
	{
		overlay->OnDetach();
		m_LayerStack.PopLayer(overlay);
	}

	void Application::AddShader(std::string name, std::string vertPath, std::string fragPath)
	{
		m_assetManager.addShader(name, vertPath, fragPath);
	}

	void Application::InitResources(std::string pathToTextures, std::string pathToShaders)
	{
		AddTextures(pathToTextures);
		AddShaders(pathToShaders);
	}

	void Application::AddTextures(std::string pathToTextures)
	{
		std::vector<std::string> allTextures{};
		FileIO::getAllFilesInDirectory(&allTextures, pathToTextures);

		for (std::string s : allTextures)
		{
			//Extract just the filename from the path
			size_t lastSlash = s.find_last_of("/\\");
			std::string base = (lastSlash == std::string::npos) ? s : s.substr(lastSlash + 1);
			size_t lastDot = base.find_last_of('.');
			std::string texName = (lastDot == std::string::npos || lastDot == 0) ? base : base.substr(0, lastDot);

			AddTexture(texName, s);
		}
	}

	void Application::AddShaders(std::string pathToShaders)
	{
		std::vector<std::string> allShaders{};
		FileIO::getAllFilesInDirectory(&allShaders, pathToShaders);

		//Separate shaders into frags and verts
		//TODO is this guaranteed to be robust, as it assumes getAllFilesInDirectory adds files in pairs and in the same order (.frag then .vert). Might be better to just combine .vert and .frag into one file, and split programatically?
		std::vector<std::string> allVerts{};
		std::vector<std::string> allFrags{};

		for (i32 i = 0; i < allShaders.size(); i += 2)
		{
			allFrags.push_back(allShaders.at(i));
			allVerts.push_back(allShaders.at(i + 1));
		}

		i32 idx = 0;
		for (std::string s : allVerts)
		{
			//Extract just the filename from the path
			size_t lastSlash = s.find_last_of("/\\");
			std::string base = (lastSlash == std::string::npos) ? s : s.substr(lastSlash + 1);
			size_t lastDot = base.find_last_of('.');
			std::string shaderName = (lastDot == std::string::npos || lastDot == 0) ? base : base.substr(0, lastDot);

			AddShader(shaderName, s, allFrags.at(idx));
			idx++;
		}
	}

	Shader* Application::GetShader(std::string name)
	{
		return m_assetManager.getShader(name);
	}
	
	void Application::AddTexture(std::string name, std::string filepath)
	{
		m_assetManager.addTexture(name, filepath);
	}
	
	
	Texture* Application::GetTexture(std::string name)
	{
		return m_assetManager.getTexture(name);
	}
}