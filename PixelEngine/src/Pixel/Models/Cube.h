#pragma once
#include "Pixel/Models/Model.h"

namespace Pixel
{
	class Cube : public Model
	{
	public:
		Cube(
			AssetManager& assets, std::string name, std::string shaderName, std::vector<std::string> textureNames = {})
			: Model(assets,std::move(name),vertices(),indices(),std::move(shaderName),std::move(textureNames))
		{}
		~Cube() {}

	private:
		static const std::vector<f32>& vertices()
		{
			static const std::vector<f32> data = {
				// Front (+Z)
				-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
				 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
				-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,

				// Back (-Z)
				 0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
				-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
				 0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

				 // Right (+X)
				  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
				  0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
				  0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
				  0.5f,  0.5f,  0.5f, 0.0f, 1.0f,

				  // Left (-X)
				  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
				  -0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
				  -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
				  -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

				  // Top (+Y)
				  -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
				   0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
				   0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
				  -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

				  // Bottom (-Y)
				  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
				   0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
				   0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
				  -0.5f, -0.5f,  0.5f, 0.0f, 1.0f
			};

			return data;
		}

		static const std::vector<ui32>& indices()
		{
			static const std::vector<ui32> data = {
				 0,  1,  2,  2,  3,  0, // Front
				 4,  5,  6,  6,  7,  4, // Back
				 8,  9, 10, 10, 11,  8, // Right
				12, 13, 14, 14, 15, 12, // Left
				16, 17, 18, 18, 19, 16, // Top
				20, 21, 22, 22, 23, 20  // Bottom
			};

			return data;
		}
	};
	
}