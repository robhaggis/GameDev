
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

	void setShader(Pixel::Shader* shader) { m_Shader = shader; }

private:
	Pixel::Shader* m_Shader;
	std::vector<f32> vertices;
	std::vector<ui32> indices;

};