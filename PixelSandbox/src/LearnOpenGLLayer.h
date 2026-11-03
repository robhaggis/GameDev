
#pragma once
#include <Pixel/Layer.h>
#include <Pixel/Shader.h>
#include <Pixel/Window/Window.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include "PixelAppConfig.h"

class LearnOpenGLLayer : public Pixel::Layer
{
public:
	LearnOpenGLLayer();
	~LearnOpenGLLayer();
	

	void OnAttach() override;
	void OnUpdate() override;
	void OnDetach() override;
	void processInput(Pixel::InputData* inputs) override;

private:
	Pixel::Shader* m_Shader;
	Pixel::Texture* m_Texture1;
	Pixel::Texture* m_Texture2;

	std::vector<f32> vertices;
	std::vector<ui32> indices;

	f32 m_mixValue = 0.01f;
	f32 m_RotateAngle = 0.0f;

	// Track previous frame button state for edge detection
	bool m_PrevMouseButtonState[8] = {};
};