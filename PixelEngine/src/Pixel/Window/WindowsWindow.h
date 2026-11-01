#pragma once
#include "Pixel/Core.h"
#include "Pixel/Log.h"
#include "Window.h"
#include "..\Application.h"

#include "GLFW/glfw3.h"


namespace Pixel
{
	struct WindowData
	{
		ui32 m_Width;
		ui32 m_Height;
		char* m_Title;
	};


	class PIXEL_API WindowsWindow : public Window
	{
	public:

		WindowsWindow();
		WindowsWindow(ui32 width, ui32 height, const char* title);
		
		~WindowsWindow() override;

		inline ui32 getWidth() override;
		inline ui32 getHeight() override;
		inline const char* getTitle() const { return m_winData.m_Title; }

		void update() override;
		void processInput(InputData* input);

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	private:
		GLFWwindow* m_GLFWWindow;
		WindowData m_winData;

		static bool s_glfwInitialized;

		void init();

	};
}

