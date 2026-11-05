#pragma once
#include "Pixel/Core.h"
#include "Pixel/Log.h"
#include "Pixel/Shader.h"
#include "Pixel/Texture.h"
#include "Pixel/Model.h"

#include "glad.h"
#include "GLFW/glfw3.h"

namespace Pixel
{

	struct RenderCommand
	{
		ui32 VAO;
		ui32 shaderID;
		glm::mat4 transform;
		i32 modelLoc;
		std::vector<ui32> textureIDs;
	};

	class PIXEL_API Renderer
	{
	public:

		Renderer();
		~Renderer();

		void submit(Model* model, glm::mat4 transform);
		void flush(const glm::mat4& view, const glm::mat4& projection);

	private:
		std::vector<RenderCommand> m_RenderQueue;
	};
}

