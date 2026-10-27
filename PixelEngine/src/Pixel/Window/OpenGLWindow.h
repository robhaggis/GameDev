#pragma once
#include "Pixel/Core.h"
#include "Pixel/Log.h"
#include "Window.h"

namespace Pixel
{
	class PIXEL_API OpenGLWindow : public Window
	{
	public:

		OpenGLWindow();
		OpenGLWindow(ui32 width, ui32 height, const char* title);
		~OpenGLWindow() override;

		inline const char* getTitle() const { return m_Title; }

		void update() override;
		void render() override;
		void clear() override;
	private:
		char* m_Title;
	};
}

