#pragma once
#include "Pixel/Application.h"

#ifdef PIXEL_PLATFORM_WINDOWS

extern Pixel::Application* Pixel::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Pixel::CreateApplication();
	app->Run();
	delete app;
}

#endif