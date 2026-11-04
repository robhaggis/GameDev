#pragma once

#include "Pixel/Core.h"
#include "Pixel/Log.h"

namespace Pixel
{
	//Struct to hold the state of all player inputs, so it can be accessed by the application class
	struct PIXEL_API WindowData
	{
		//Window Params
		f32 windowWidth;
		f32 windowHeight;

		//Frame timing
		f32 deltaTime{};
		f32 lastFrame{};
		
		//Keys
		bool isKeyPressed[512]{};
		bool isKeyJustPressed[512]{};

		//Mouse
		f32 mouseX = windowWidth / 2.0f;
		f32 mouseY = windowHeight / 2.0f;
		f32 lastMouseX = mouseX;
		f32 lastMouseY = mouseY;
		f32 mouseXOffset = 0.0f;
		f32 mouseYOffset = 0.0f;
		f64 mouseScrollOffset = 0.0f;
		bool isMouseButtonPressed[8]{};
		bool isMouseButtonJustPressed[8]{};
		bool m_PrevMouseButtonState[8]{};
		bool isMouseLookEnabled = true;
	};


	class PIXEL_API Window
	{

	public:
		virtual ~Window() {}

		virtual void update() = 0;

		virtual inline ui32 getWidth() = 0;
		virtual inline ui32 getHeight() = 0;
		virtual void processInput(WindowData* data) = 0;
		virtual void clear() = 0;
		virtual inline bool windowShouldClose() = 0;
		virtual void toggleMouseCapture() = 0;;

		static Window* create();
		static Window* create(ui32 width, ui32 height, const char* title);


	};
}


