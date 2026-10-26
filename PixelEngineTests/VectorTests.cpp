#include <gtest/gtest.h>
#include "Pixel/Vector.h"

namespace MathsTest
{
	TEST(VectorTests, Vec2iInitialization)
	{
		Pixel::Vec2i vec{ -3, 4 };
		EXPECT_EQ(vec.x, -3);
		EXPECT_EQ(vec.y, 4);
	}

	TEST(VectorTests, Vec2uiInitialization)
	{
		Pixel::Vec2ui vec{ 3, 4 };
		EXPECT_EQ(vec.x, 3);
		EXPECT_EQ(vec.y, 4);
	}

	TEST(VectorTests, Vec2fInitialization)
	{
		Pixel::Vec2f vec{ 3.0f, 4.0f };
		EXPECT_EQ(vec.x, 3.0f);
		EXPECT_EQ(vec.y, 4.0f);
	}
}