#include <gtest/gtest.h>
#include "Pixel/Window/OpenGLWindow.h"

namespace PixelEngineTest
{
	TEST(OpenGLWindowTest, OpenGLWindowDefaultInstantiatesCorrectly)
	{
		Pixel::Log::Init();
		Pixel::OpenGLWindow* win = new Pixel::OpenGLWindow();

		//NOTE these values are hardcoded into default constructor in OpenGLWindow.cpp
		EXPECT_EQ(win->getWidth(), 1280);
		EXPECT_EQ(win->getHeight(), 720);
		EXPECT_STREQ(win->getTitle(), "PixelENGINE");
		delete win;
	}

	TEST(OpenGLWindowTest, OpenGLWindowInstantiatesCorrectlyWithParameters)
	{
		Pixel::Log::Init();
		Pixel::OpenGLWindow* win = new Pixel::OpenGLWindow(500,600,"Test Title");

		EXPECT_EQ(win->getWidth(), 500);
		EXPECT_EQ(win->getHeight(), 600);
		EXPECT_STREQ(win->getTitle(), "Test Title");
		delete win;
	}
}
