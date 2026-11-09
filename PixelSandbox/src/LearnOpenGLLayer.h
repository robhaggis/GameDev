
#pragma once
#include <Pixel.h>
#include "PixelAppConfig.h"




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
	
	std::vector<Pixel::Model*> m_Models;
	//Pixel::Cube* m_Cube;
};