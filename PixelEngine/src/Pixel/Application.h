#pragma once

#include "Core.h"
namespace Pixel
{
	class PIXEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in client app
	Application* CreateApplication();
}

