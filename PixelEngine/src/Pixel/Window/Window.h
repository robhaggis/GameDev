#pragma once

#include "Pixel/Core.h"
#include "Pixel/Log.h"

namespace Pixel
{
	class PIXEL_API Window
	{

	public:
		virtual ~Window() {}

		virtual void update() = 0;
		virtual void processInput() = 0;

		virtual inline ui32 getWidth() = 0;
		virtual inline ui32 getHeight() = 0;

		bool m_WindowShouldClose = false;

		static Window* create();
		static Window* create(ui32 width, ui32 height, const char* title);

	};
}


