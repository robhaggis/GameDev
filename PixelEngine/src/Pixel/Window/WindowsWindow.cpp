#include "PixelPCH.h"
#include "WindowsWindow.h"

namespace Pixel
{

	bool WindowsWindow::s_glfwInitialized = false;

	WindowsWindow::WindowsWindow()
	{
		m_winData.m_Width = 1280;
		m_winData.m_Height = 720;

		const char* source = "PixelENGINE";
		const std::size_t length = std::strlen(source) + 1;
		m_winData.m_Title = new char[length];
		std::memcpy(m_winData.m_Title, source, length);
		init();
	}

	WindowsWindow::WindowsWindow(ui32 width, ui32 height, const char* title)
	{
		m_winData.m_Width = width;
		m_winData.m_Height = height;
		//Uses char* instead of std::string so m_Title can be exposed across the dll
		// boundary, mainly for TEST
		const char* source = title ? title : "";
		const std::size_t length = std::strlen(source) + 1;
		m_winData.m_Title = new char[length];
		std::memcpy(m_winData.m_Title, source, length);
		init();
	}

	WindowsWindow::~WindowsWindow()
	{
		delete[] m_winData.m_Title;
		glfwDestroyWindow(m_GLFWWindow);
		glfwTerminate();
	}

	Window* Window::create()
	{
		return new WindowsWindow();
	}

	Window* Window::create(ui32 width, ui32 height, const char* title)
	{
		return new WindowsWindow(width, height, title);
	}

	inline ui32 WindowsWindow::getWidth()
	{
		return m_winData.m_Width;
	}

	inline ui32 WindowsWindow::getHeight()
	{
		return m_winData.m_Height;
	}

	void WindowsWindow::update()
	{
		glfwSwapBuffers(m_GLFWWindow);
		glfwPollEvents();
	}

	void WindowsWindow::processInput(InputData* data)
	{
		if (glfwWindowShouldClose(m_GLFWWindow))
		{
			data->windowShouldClose = true;
		}

		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			data->windowShouldClose = true;
		}

		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_UP) == GLFW_PRESS)
		{
			data->upKeyPressed = true;
		}
		else
		{
			data->upKeyPressed = false;
		}

		if (glfwGetKey(m_GLFWWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			data->downKeyPressed = true;
		}
		else
		{
			data->downKeyPressed = false;
		}

	}

	void WindowsWindow::clear()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void WindowsWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}


	void WindowsWindow::init()
	{
		PIX_CORE_INFO("Creating Windows Window '{0}' ({1}, {2})...", m_winData.m_Title, m_winData.m_Width, m_winData.m_Height);

		if (!s_glfwInitialized)
		{
			i32 success = glfwInit();
			if (!success)
			{
				PIX_CORE_FATAL("Failed to Init GLFW");
				glfwTerminate();
				return;
			}
			WindowsWindow::s_glfwInitialized = true;

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			
			m_GLFWWindow = glfwCreateWindow((i32)m_winData.m_Width, (i32)m_winData.m_Height, m_winData.m_Title, NULL, NULL);
			PIX_CORE_INFO("Window Created successfully");
			glfwMakeContextCurrent(m_GLFWWindow);
			glfwSetWindowUserPointer(m_GLFWWindow, &m_winData);

			//Init GLAD
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				PIX_CORE_FATAL("Failed to initialise GLAD");
				return;
			}

			//Register Callbacks
			glfwSetFramebufferSizeCallback(m_GLFWWindow, framebuffer_size_callback);
			
		}
	}	
}
