#pragma once
#include "Pixel/Application.h"

#ifdef PIXEL_PLATFORM_WINDOWS

extern Pixel::Application* Pixel::CreateApplication();

int main(int argc, char** argv)
{
	Pixel::Log::Init();
	PIX_CORE_INFO("Log Init Successful");
	int a = 5;
	PIX_TRACE("Test Message from App logger. var = {0}", a);

	auto app = Pixel::CreateApplication();
	app->Run();
	delete app;
}

#endif