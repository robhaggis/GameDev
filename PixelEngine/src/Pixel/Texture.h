#pragma once

#include "Core.h"
#include "Log.h"

#include "glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

namespace Pixel
{
	class PIXEL_API Texture
	{
	public:
		Texture(std::string filepath);
		~Texture();

		inline const GLuint ID() { return m_texID; }

	private:
		ui32 m_texID;
	};

}



