#pragma once
#include "Pixel/Application.h"

#include "PixelAppConfig.h"

#include <crtdbg.h>

#ifdef PIXEL_PLATFORM_WINDOWS

extern Pixel::Application* Pixel::CreateApplication(ui32 width, ui32 height, const char* title);

int main(int argc, char** argv)
{
#ifdef _DEBUG
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	}
#endif
	Pixel::Log::Init();
	PIX_CORE_INFO("Log Init Successful");

	auto app = Pixel::CreateApplication(Pixel::APP_WIDTH, Pixel::APP_HEIGHT, Pixel::APP_TITLE);
	app->run();
	delete app;
}

#endif