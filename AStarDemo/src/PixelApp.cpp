#include "Pixel/EntryPoint.h"
#include <Pixel.h>

#include "AStarDemo.h"



class PixelApp : public Pixel::Application
{
public:
	PixelApp(ui32 width, ui32 height, const char* title)
		:Pixel::Application(width, height, title)
	{		
		AddShader("Texture","../PixelSandbox/res/shaders/texture.vert", "../PixelSandbox/res/shaders/texture.frag");

		AddTexture("BlueBorder", "../AStarDemo/res/textures/BlueBorder.png");;

		//Add Layers to application
		glLayer = new AStarDemoLayer();
		PushLayer(glLayer);

	}
	~PixelApp()
	{
		//NOTE Be careful deleting things in here, a lot of clean up is handled by the engine, so be wary of double deletes
	}

private:
	AStarDemoLayer* glLayer;

};

Pixel::Application* Pixel::CreateApplication(ui32 width, ui32 height, const char* title)
{
	return new PixelApp(width, height, title);
}


