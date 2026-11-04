
#pragma once
#include <Pixel.h>
#include "PixelAppConfig.h"

#include "Camera.h"

class LearnOpenGLLayer : public Pixel::Layer
{
public:
	LearnOpenGLLayer();
	~LearnOpenGLLayer();
	
	void OnAttach() override;
	void OnUpdate() override;
	void OnDetach() override;
	void processInput(Pixel::WindowData* inputs) override;

private:
	Pixel::Shader* m_Shader;
	Pixel::Texture* m_Texture1;
	Pixel::Texture* m_Texture2;

	std::vector<f32> vertices;
	std::vector<ui32> indices;
	std::vector<glm::vec3> cubePositions;

	f32 m_mixValue = 0.01f;
	
	Camera* m_Camera;

	
};