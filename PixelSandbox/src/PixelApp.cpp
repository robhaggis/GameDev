#include <Pixel.h>


class ExampleLayer : public Pixel::Layer 
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		PIX_INFO("ExampleLayer::OnUpdate");
	}

	void OnAttach() override
	{
		PIX_INFO("ExampleLayer::OnAttach");
	}

	void OnDetach()override
	{
		PIX_INFO("ExampleLayer::OnDetach");
	}

};


class PixelApp : public Pixel::Application
{
public:
	PixelApp(ui32 width, ui32 height, const char* title)
		:Pixel::Application(width, height, title)
	{
		PushLayer(new ExampleLayer());
	}
	~PixelApp()
	{

	}

};

Pixel::Application* Pixel::CreateApplication(ui32 width, ui32 height, const char* title)
{
	return new PixelApp(width, height, title);
}


