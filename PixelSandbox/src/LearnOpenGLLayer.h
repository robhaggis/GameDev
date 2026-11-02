
#pragma once
#include <Pixel/Layer.h>
#include <Pixel/Shader.h>

class LearnOpenGLLayer : public Pixel::Layer
{
public:
	LearnOpenGLLayer();
	~LearnOpenGLLayer();
	

	void OnAttach() override;
	void OnUpdate() override;
	void OnDetach() override;

private:
	Pixel::Shader* m_Shader;
	Pixel::Texture* m_Texture1;
	Pixel::Texture* m_Texture2;

	std::vector<f32> vertices;
	std::vector<ui32> indices;

	i32 m_mixValue;
};