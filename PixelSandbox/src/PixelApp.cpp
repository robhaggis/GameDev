#include <Pixel.h>

#include "LearnOpenGLLayer.h"



class PixelApp : public Pixel::Application
{
public:
	PixelApp(ui32 width, ui32 height, const char* title)
		:Pixel::Application(width, height, title)
	{
		//Add resources to asset pool
		AddShader("Basic", "../PixelSandbox/res/shaders/basic.vert", "../PixelSandbox/res/shaders/basic.frag");

		//Add Layers to application
		glLayer = new LearnOpenGLLayer();
		PushLayer(glLayer);

		//Push resources out to layers
		glLayer->setShader(GetShader("Basic"));


	}
	~PixelApp()
	{
		//NOTE Be careful deleting things in here, a lot of clean up is handled by the engine, so be wary of double deletes
	}

private:
	LearnOpenGLLayer* glLayer;

};

Pixel::Application* Pixel::CreateApplication(ui32 width, ui32 height, const char* title)
{
	return new PixelApp(width, height, title);
}


