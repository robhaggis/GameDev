#include "PixelPCH.h"
#include "OpenGLWindow.h"

namespace Pixel
{
	OpenGLWindow::OpenGLWindow()
		:Window(1280, 720), m_Title(nullptr)
	{
		const char* source = "PixelENGINE";
		const std::size_t length = std::strlen(source) + 1;
		m_Title = new char[length];
		std::memcpy(m_Title, source, length);
	}

	OpenGLWindow::OpenGLWindow(ui32 width, ui32 height, const char* title)
		:Window(width, height), m_Title(nullptr)
	{
		//Uses char* instead of std::string so m_Title can be exposed across the dll
		// boundary, mainly for TEST
		const char* source = title ? title : "";
		const std::size_t length = std::strlen(source) + 1;
		m_Title = new char[length];
		std::memcpy(m_Title, source, length);
	}

	OpenGLWindow::~OpenGLWindow()
	{
		delete[] m_Title;
	}

	void OpenGLWindow::update()
	{}

	void OpenGLWindow::render()
	{}

	void OpenGLWindow::clear()
	{}
}
