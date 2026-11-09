#pragma once
#include "Pixel/Core.h"
#include "Pixel/Log.h"
#include "Pixel/Shader.h"
#include "Pixel/Texture.h"
#include "Pixel/Models/Model.h"
#include "RenderCommand.h"

#include "glad.h"
#include "GLFW/glfw3.h"

namespace Pixel
{
	class PIXEL_API Renderer
	{
	public:

		Renderer();
		~Renderer();

		void submit(const RenderCommand& rc);
		void flush();

	private:
		std::vector<RenderCommand> m_RenderQueue;
	};
}

