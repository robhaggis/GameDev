#include "PixelPCH.h"
#include "Texture.h"

namespace Pixel
{
	Texture::Texture(std::string filepath)
		:m_texID(0)
	{
		glGenTextures(1, &m_texID);
		glBindTexture(GL_TEXTURE_2D, m_texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		i32 width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 4);
		if (nrChannels != 4)
		{
			PIX_CORE_WARN("Only 4 channel, 32 bit, RGBA images currently supported");
		}
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			PIX_CORE_WARN("Failed to Load Texture at '{0}'", filepath);
			PIX_CORE_TRACE(stbi_failure_reason());
		}
		stbi_image_free(data);
	}
	Texture::~Texture()
	{
	
	}
}
