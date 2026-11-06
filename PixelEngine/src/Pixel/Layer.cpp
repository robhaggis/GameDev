#include "PixelPCH.h"
#include "Layer.h"

Pixel::Layer::Layer(const std::string& name)
	:m_DebugName(name), m_IsEnabled(true), m_Camera(nullptr)
{
	
}

Pixel::Layer::~Layer()
{
	delete m_Renderer;
	delete m_AssetManager;
	delete m_Camera;
}

void Pixel::Layer::InitCamera(glm::vec3 pos, glm::vec3 up, glm::vec3 right)
{
	if (m_Camera == nullptr)
	{
		m_Camera = new Camera(glm::vec3{ 0,0,3.0f }, glm::vec3{ 0,1,0 }, glm::vec3{ 0,0,-1.0f });
	}
	else
	{
		PIX_CORE_WARN("Camera already initialised on Layer {0}", m_DebugName);
	}
}





