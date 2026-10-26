#include "PixelPCH.h"
#include "Window.h"

Pixel::Window::Window(i32 width, i32 height, const char* title)
	:m_Width(width), m_Height(height), m_Title(nullptr)
{
	const char* source = title ? title : "";
	const std::size_t length = std::strlen(source) + 1;
	m_Title = new char[length];
	std::memcpy(m_Title, source, length);
}

Pixel::Window::~Window()
{
	delete[] m_Title;
}

void Pixel::Window::update()
{

}

void Pixel::Window::render()
{

}
