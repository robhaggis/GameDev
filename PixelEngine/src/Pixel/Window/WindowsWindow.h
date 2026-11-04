#pragma once
#include "Pixel/Core.h"
#include "Pixel/Log.h"
#include "Window.h"
#include "..\Application.h"

#include "glad.h"
#include "GLFW/glfw3.h"


namespace Pixel
{
	struct NativeWindowData
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
		void processInput(WindowData* input);
		void clear() override;
		inline bool windowShouldClose() override { return glfwWindowShouldClose(m_GLFWWindow); }
		void WindowsWindow::toggleMouseCapture() override;
		

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void cursor_position_callback(GLFWwindow* window, f64 xpos, f64 ypos);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void window_close_callback(GLFWwindow* window);
		static void mouse_scroll_callback(GLFWwindow* window, f64 xOffset, f64 yOffset);
	

	private:
		GLFWwindow* m_GLFWWindow;
		NativeWindowData m_winData;

		static bool s_glfwInitialized;
	
		//For passing values to the Input Data Struct
		static bool m_Keys[512];
		static bool m_MouseButtons[8];
		static f64 m_MouseScrollOffset;
		static f64 m_CursorXPos;
		static f64 m_CursorYPos;	
		bool m_FirstMouseInput = true;
		bool m_MouseLookEnabled = true;

		void init();

	};
}

