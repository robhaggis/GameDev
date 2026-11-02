
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
	Shader* m_Shader;

	const char* vertexShaderSource = "#version 450 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 450 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
};