#include <Pixel.h>

#include "LearnOpenGLLayer.h"



class PixelApp : public Pixel::Application
{
public:
	PixelApp(ui32 width, ui32 height, const char* title)
		:Pixel::Application(width, height, title)
	{
		//Add resources to asset Manager
		AddShader("Basic", "../PixelSandbox/res/shaders/basic.vert", "../PixelSandbox/res/shaders/basic.frag");
		AddShader("Texture","../PixelSandbox/res/shaders/texture.vert", "../PixelSandbox/res/shaders/texture.frag");
		AddTexture("WoodContainer", "../PixelSandbox/res/textures/container.png");
		AddTexture("Harvey", "../PixelSandbox/res/textures/harvey.png");

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


