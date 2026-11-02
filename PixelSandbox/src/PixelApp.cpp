#include <Pixel.h>

#include "LearnOpenGLLayer.h"



class PixelApp : public Pixel::Application
{
public:
	PixelApp(ui32 width, ui32 height, const char* title)
		:Pixel::Application(width, height, title)
	{
		PushLayer(new LearnOpenGLLayer());
	}
	~PixelApp()
	{

	}

};

Pixel::Application* Pixel::CreateApplication(ui32 width, ui32 height, const char* title)
{
	return new PixelApp(width, height, title);
}


