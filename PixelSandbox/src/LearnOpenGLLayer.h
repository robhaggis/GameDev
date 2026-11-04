
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
	void processInput(Pixel::WindowData* inputs) override;

private:
	Pixel::Shader* m_Shader;
	Pixel::Texture* m_Texture1;
	Pixel::Texture* m_Texture2;

	std::vector<f32> vertices;
	std::vector<ui32> indices;
	std::vector<glm::vec3> cubePositions;

	f32 m_mixValue = 0.01f;
	f32 m_RotateAngle = 0.0f;

	glm::vec3 m_CamPos{ 0.0f,0.0f,10.0f};
	glm::vec3 m_CamFront{ 0.0f,0.0f,-1.0f };
	glm::vec3 m_CamUp{ 0.0f, 1.0f, 0.0f };

	f32 m_CamYaw = -90.0f;
	f32 m_CamPitch = 0.0f;
	f32 m_CamFOV = 45.0f;
	const f32 m_MouseLookSensitivity = 0.25f;
	f32 m_CamWalkSpeeed = 5.0f;
	const f32 m_MouseZoomSensitivity = 1.0f;
};