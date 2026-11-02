
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
};