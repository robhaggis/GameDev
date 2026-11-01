#pragma once
#include "Pixel/Application.h"

#include "PixelAppConfig.h"

#ifdef PIXEL_PLATFORM_WINDOWS

extern Pixel::Application* Pixel::CreateApplication(ui32 width, ui32 height, const char* title);

int main(int argc, char** argv)
{
	Pixel::Log::Init();
	PIX_CORE_INFO("Log Init Successful");

	auto app = Pixel::CreateApplication(Pixel::APP_WIDTH, Pixel::APP_HEIGHT, Pixel::APP_TITLE);
	app->run();
	delete app;
}

#endif