#pragma once

#include "Core.h"

namespace Pixel
{
	class PIXEL_API Window
	{
	public:
		Window(i32 width, i32 height, const char* title);
		~Window();

		void update();
		void render();

		inline i32 getWidth() const { return m_Width; }
		inline i32 getHeight() const { return m_Height; }
		inline const char* getTitle() const { return m_Title; }

	private:
		i32 m_Width;
		i32 m_Height;
		char* m_Title;
	};
}


