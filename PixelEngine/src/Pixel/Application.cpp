#include "PixelPCH.h"
#include "Application.h"

namespace Pixel
{
	Application::Application(i32 width, i32 height, const char* title)
		:m_Window(nullptr)
	{
		m_Window = std::unique_ptr<Window>(Window::create(width, height, title));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (m_isRunning && !inputData.windowShouldClose)
		{
			m_Window->processInput(&inputData);

			m_Window->clear();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
			m_Window->update();
		}
		m_isRunning = false;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLay(Layer * overlay)
	{
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
}