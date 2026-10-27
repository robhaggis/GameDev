#pragma once

#include "Core.h"
namespace Pixel
{
	class PIXEL_API Application
	{
	public:
		Application();
		Application(i32 width, i32 height, const char* title);
		virtual ~Application();

		void Run();

	private:
	};

	//To be defined in client app
	Application* CreateApplication();
}

