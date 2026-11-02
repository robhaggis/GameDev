#pragma once

#include "Core.h"
#include "Window/Window.h"
#include "LayerStack.h"


namespace Pixel
{
	
	class PIXEL_API Application
	{

	public:
		Application(i32 width, i32 height, const char* title);
		virtual ~Application();

		void run();

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

	private:
		std::unique_ptr<Window> m_Window;
		InputData inputData;
		bool m_isRunning = true;
		LayerStack m_LayerStack;

	};

	//To be defined in client app
	Application* CreateApplication(ui32 width, ui32 height, const char* title);
}

