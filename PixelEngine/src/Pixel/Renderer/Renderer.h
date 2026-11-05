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
	class PIXEL_API Renderer
	{
	public:

		Renderer();
		~Renderer();

		void submit(Model* model);
		void flush();

	private:
		std::vector<Model*> m_RenderQueue;
	};
}

