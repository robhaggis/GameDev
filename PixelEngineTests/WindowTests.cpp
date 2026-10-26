#include <gtest/gtest.h>

#include "Pixel/Window.h"

namespace PixelTest
{
	TEST(WindowTests, WindowConstructsCorrectly)
	{
		Pixel::Window win{ 1280, 740, "Test Window" };
		EXPECT_EQ(1280, win.getWidth());
		EXPECT_EQ(740, win.getHeight());
		EXPECT_STREQ("Test Window", win.getTitle());
	}
}

