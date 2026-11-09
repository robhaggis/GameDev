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

void Pixel::Layer::InitCamera(glm::vec3 pos, glm::vec3 up, glm::vec3 front)
{
	if (m_Camera == nullptr)
	{
		m_Camera = new Camera(pos, up, front);
	}

	else
	{
		PIX_CORE_WARN("Camera already initialised on Layer {0}", m_DebugName);
	}
}





