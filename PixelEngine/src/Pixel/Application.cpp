#include "PixelPCH.h"
#include "Application.h"

namespace Pixel
{
	Application::Application(i32 width, i32 height, const char* title)
		:m_Window(nullptr)
	{
		m_Window = std::unique_ptr<Window>(Window::create(width, height, title));
		m_assetManager.Init();
	}

	Application::~Application()
	{
		m_LayerStack.RemoveAllLayers();
	}

	void Application::run()
	{
		while (m_isRunning && !m_Window->windowShouldClose())// && !m_InputData.isKeyPressed[GLFW_KEY_ESCAPE])
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
		m_LayerStack.PushLayer(layer);
		
		layer->OnAttach();
	}

	void Application::PushOverLay(Layer * overlay)
	{
		overlay->setAssetManager(&m_assetManager);
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