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

	void Application::Run()
	{
		while (m_isRunning && ! m_Window->m_WindowShouldClose)
		{
			m_Window->processInput();
			m_Window->update();
		}
		m_isRunning = false;
	}
}