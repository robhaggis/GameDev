#pragma once
#include "Pixel/Core.h"
#include "Pixel/Log.h"
#include "Pixel/Shader.h"
#include "Pixel/Texture.h"

#include "glad.h"
#include "GLFW/glfw3.h"

namespace Pixel
{
	class PIXEL_API Renderer
	{
	public:

		Renderer();
		~Renderer();

		void submit(const std::vector<f32>& vertices, const std::vector<ui32>& indices);
		void flush(Shader* shader,Texture* texture1, Texture* texture2);

	private:
		ui32 m_VAO, m_VBO, m_EBO;
		ui32 m_IndicesCount;
	};
}

