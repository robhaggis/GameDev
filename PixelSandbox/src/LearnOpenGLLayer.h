
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
	
	std::vector<glm::vec3> cubePositions;
	Pixel::Model* m_WoodenCube{};
	Pixel::Model* m_LightCube{};
	Pixel::Shader* m_Shader{};

	f32 m_mixValue = 0.01f;
	
	Camera* m_Camera;

	
};