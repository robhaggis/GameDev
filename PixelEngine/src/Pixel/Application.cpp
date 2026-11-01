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
		while (m_isRunning && !inputData.windowShouldClose)
		{
			m_Window->processInput(&inputData);
			m_Window->update();
		}
		m_isRunning = false;
	}
}