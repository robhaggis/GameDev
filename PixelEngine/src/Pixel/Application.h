#pragma once

#include "Core.h"
#include "Window/Window.h"
namespace Pixel
{
	
	class PIXEL_API Application
	{

	public:
		Application(i32 width, i32 height, const char* title);
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		InputData inputData;
		bool m_isRunning = true;

	};

	//To be defined in client app
	Application* CreateApplication(ui32 width, ui32 height, const char* title);
}

