#include "Pixel/EntryPoint.h"
#include <Pixel.h>

#include "LearnOpenGLLayer.h"



class PixelApp : public Pixel::Application
{
public:
	PixelApp(ui32 width, ui32 height, const char* title)
		:Pixel::Application(width, height, title)
	{
		InitResources("../PixelSandbox/res/textures/", "../PixelSandbox/res/shaders/");

		//Add Layers to application
		glLayer = new LearnOpenGLLayer();
		PushLayer(glLayer);

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


