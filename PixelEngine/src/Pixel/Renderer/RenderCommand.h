#pragma once
#include "pixel/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Pixel
{
	struct PIXEL_API RenderCommand
	{
		ui32 VAO;
		ui32 shaderID;
		glm::mat4 transform;
		std::vector<Texture*> textureIDs;
		i32 activeTexture;
	};
}
