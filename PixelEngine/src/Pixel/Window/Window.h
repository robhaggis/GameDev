#pragma once

#include "Pixel/Core.h"
#include "Pixel/Log.h"

namespace Pixel
{
	//Struct to hold the state of all player inputs, so it can be accessed by the application class
	struct PIXEL_API InputData
	{
		bool isKeyPressed[512]{};
		i32 mouseX;
		i32 mouseY;
		bool isMouseButtonPressed[8]{};
	};


	class PIXEL_API Window
	{

	public:
		virtual ~Window() {}

		virtual void update() = 0;

		virtual inline ui32 getWidth() = 0;
		virtual inline ui32 getHeight() = 0;
		virtual void processInput(InputData* data) = 0;
		virtual void clear() = 0;
		virtual inline bool windowShouldClose() = 0;

		static Window* create();
		static Window* create(ui32 width, ui32 height, const char* title);

	};
}


