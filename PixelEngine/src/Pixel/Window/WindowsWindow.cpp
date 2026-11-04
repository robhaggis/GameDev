#include "PixelPCH.h"
#include "WindowsWindow.h"

namespace Pixel
{

	bool WindowsWindow::s_glfwInitialized = false;
	bool WindowsWindow::m_Keys[512] = {};
	bool WindowsWindow::m_MouseButtons[8] = {};
	f64 WindowsWindow::m_CursorXPos = 0.0;
	f64 WindowsWindow::m_CursorYPos = 0.0;
	f64 WindowsWindow::m_MouseScrollOffset = 0.0;

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

	void WindowsWindow::processInput(WindowData* data)
	{
		//Frame timing
		float currentFrame = static_cast<float>(glfwGetTime());
		data->deltaTime = currentFrame - data->lastFrame;
		data->lastFrame = currentFrame;

		//Window Params
		data->windowWidth = m_winData.m_Width;
		data->windowHeight = m_winData.m_Height;
		
		//Keys
		for (int i = 0; i < 512; i++)
		{
			data->isKeyJustPressed[i] = m_Keys[i] && !data->isKeyPressed[i];
			data->isKeyPressed[i] = m_Keys[i];
		}

		//Mouse
		for (int i = 0; i < 8; i++)
		{
			data->isMouseButtonPressed[i] = m_MouseButtons[i];
			data->isMouseButtonJustPressed[i] =
				data->isMouseButtonPressed[i] && !data->m_PrevMouseButtonState[i];
			data->m_PrevMouseButtonState[i] = data->isMouseButtonPressed[i];
		}

		data->isMouseLookEnabled = m_MouseLookEnabled;

		if (m_MouseLookEnabled)
		{
			if (m_FirstMouseInput)
			{
				glfwGetCursorPos(m_GLFWWindow, &m_CursorXPos, &m_CursorYPos);
				data->lastMouseX = static_cast<f32>(m_CursorXPos);
				data->lastMouseY = static_cast<f32>(m_CursorYPos);
				m_FirstMouseInput = false;
			}
			data->mouseX = static_cast<f32>(m_CursorXPos);
			data->mouseY = static_cast<f32>(m_CursorYPos);
			data->mouseXOffset = data->mouseX - data->lastMouseX;
			data->mouseYOffset = data->mouseY - data->lastMouseY;
			data->lastMouseX = data->mouseX;
			data->lastMouseY = data->mouseY;
			//data->mouseXOffset *= data->mouseLookSensitivity;
			//data->mouseYOffset *= data->mouseLookSensitivity;
		}

		data->mouseScrollOffset = m_MouseScrollOffset;
		m_MouseScrollOffset = 0.0f;
	}

	void WindowsWindow::clear()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void WindowsWindow::toggleMouseCapture()
	{
		if (glfwGetInputMode(m_GLFWWindow, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
		{
			glfwSetInputMode(m_GLFWWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			m_MouseLookEnabled = false;
		}
		else if(glfwGetInputMode(m_GLFWWindow, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
		{
			glfwSetInputMode(m_GLFWWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			m_MouseLookEnabled = true;
		}	
	}

	void WindowsWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
		auto* data = static_cast<NativeWindowData*>(glfwGetWindowUserPointer(window));
		if (data)
		{
			data->m_Width = static_cast<ui32>(width);
			data->m_Height = static_cast<ui32>(height);
		}
	}

	void WindowsWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			static f64 lastClickTime[1024] = {};
			static const f64 debounceDelay = 0.05;			//50ms debounce
			f64 currentTime = glfwGetTime();
			if (currentTime - lastClickTime[key] >= debounceDelay)
			{
				 m_Keys[key] = true;
				lastClickTime[key] = currentTime;
			}
		}
		if (action == GLFW_RELEASE)
		{
			m_Keys[key] = false;
		}
	}

	void WindowsWindow::cursor_position_callback(GLFWwindow* window, f64 xpos, f64 ypos)
	{
		m_CursorXPos = xpos;
		m_CursorYPos = ypos;
	}

	void WindowsWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			static f64 lastClickTime[8] = {};
			static const f64 debounceDelay = 0.05;			//50ms debounce
			f64 currentTime = glfwGetTime();
			if (currentTime - lastClickTime[button] >= debounceDelay)
			{
				m_MouseButtons[button] = true;
				lastClickTime[button] = currentTime;
			}
		}
		else if (action == GLFW_RELEASE)
		{
			// Only process the release if the press was registered
			if (m_MouseButtons[button])
			{
				m_MouseButtons[button] = false;
			}
		}
	}

	void WindowsWindow::window_close_callback(GLFWwindow* window)
	{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	void WindowsWindow::mouse_scroll_callback(GLFWwindow* window, f64 xOffset, f64 yOffset)
	{
		m_MouseScrollOffset = +yOffset;
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
			glfwSetWindowPos(m_GLFWWindow, 500, 400);
			PIX_CORE_INFO("Window Created successfully");
			glfwMakeContextCurrent(m_GLFWWindow);
			glfwSetWindowUserPointer(m_GLFWWindow, &m_winData);

			//Init GLAD
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				PIX_CORE_FATAL("Failed to initialise GLAD");
				return;
			}

			glEnable(GL_DEPTH_TEST);
			glfwSetInputMode(m_GLFWWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			//Register Callbacks
			glfwSetFramebufferSizeCallback(m_GLFWWindow, framebuffer_size_callback);
			glfwSetWindowCloseCallback(m_GLFWWindow, window_close_callback);
			glfwSetKeyCallback(m_GLFWWindow, WindowsWindow::key_callback);
			glfwSetCursorPosCallback(m_GLFWWindow, WindowsWindow::cursor_position_callback);
			glfwSetMouseButtonCallback(m_GLFWWindow, WindowsWindow::mouse_button_callback);
			glfwSetScrollCallback(m_GLFWWindow, WindowsWindow::mouse_scroll_callback);
			
		}
	}	
}
