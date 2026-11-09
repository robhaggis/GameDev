#pragma once
#include "pixel/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Pixel
{

	using UniformValue = std::variant<bool, i32, f32, glm::vec2, glm::vec3, glm::vec4, glm::mat2, glm::mat3, glm::mat4>;

	struct Uniform
	{
		std::string name;
		UniformValue value;

	};

	struct PIXEL_API RenderCommand
	{
		ui32 VAO{};
		ui32 indicesCount{};

		std::vector<Texture*> textureIDs{};

		Shader* shader{};
		std::vector<Uniform> uniforms;
	};
}
