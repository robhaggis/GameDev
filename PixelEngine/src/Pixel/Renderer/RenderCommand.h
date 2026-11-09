#pragma once
#include "pixel/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Pixel
{
	struct PIXEL_API RenderCommand
	{
		ui32 VAO{};
		ui32 indicesCount{};

		ui32 shaderID{};

		glm::mat4 transform{};
		glm::mat4 projection{};
		glm::mat4 view{};

		std::vector<Texture*> textureIDs{};
	};
}
